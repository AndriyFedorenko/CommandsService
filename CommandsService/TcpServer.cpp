//
// Created by andrii on 27.08.21.
//

#include <thread>

#include <event.h>
#include <event2/thread.h>
#include <glog/logging.h>

#include "TcpServer.h"
#include "ClientException.h"
#include "Utils.h"

using namespace std;


TcpServer::TcpServer(
        IDataProcessor::Ptr dataProcessor,
        const std::string& address,
        const int port) :
        _dataProcessor(dataProcessor),
        _address(address),
        _port(port)
{
}

TcpServer::~TcpServer()
{
    close(_serverConnection.fileDescriptor);
}

namespace {
    const int DEFAULT_CONNECTION_MAX_NUM = 1000;
    const ssize_t READ_BUFF_SIZE = 128;
}

void TcpServer::run()
{
    connect(DEFAULT_CONNECTION_MAX_NUM);

    _serverConnection.base = Utils::makeEventBase();
    _serverConnection.acceptEvent = Utils::makeEvent(_serverConnection.base, _serverConnection.fileDescriptor,
                                              &_serverConnection, onAccept, EV_READ | EV_PERSIST);

    if(event_add(_serverConnection.acceptEvent.get(), NULL) < 0)
        throw runtime_error("event_add() failed");

    evthread_use_pthreads();

    _dataProcessor->process();

    if(event_base_dispatch(_serverConnection.base.get()) < 0)
        throw runtime_error("event_base_dispatch() failed");
}

void TcpServer::connect(const int connectionNum)
{
    _serverConnection.fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(_serverConnection.fileDescriptor  < 0)
        throw runtime_error("socket() failed!");

    if(evutil_make_socket_nonblocking(_serverConnection.fileDescriptor) < 0)
        throw runtime_error("evutil_make_socket_nonblocking() failed!");

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(_port);
    sin.sin_addr.s_addr = inet_addr(_address.c_str());

    if(bind(_serverConnection.fileDescriptor, (struct sockaddr*)&sin, sizeof(sin)) < 0)
        throw runtime_error("bind() failed");

    if(listen(_serverConnection.fileDescriptor, connectionNum) < 0)
        throw runtime_error("listen() failed");
}

void TcpServer::onAccept(evutil_socket_t listen_sock, short flags, void* arg)
{
    try
    {
        if(arg == nullptr)
            throw runtime_error( "arg is null");

        ServerConnection *serverConn = (ServerConnection *) arg;
        evutil_socket_t fileDescriptor = accept(listen_sock, 0, 0);

        if (fileDescriptor < 0)
            throw runtime_error("accept() failed");

        ClientPackage* newClientPackage = new ClientPackage(fileDescriptor, serverConn->base);

        newClientPackage->setReadEven(Utils::makeEvent(newClientPackage->getBase(), fileDescriptor,
                                                       newClientPackage, onRead, EV_READ | EV_PERSIST));
        newClientPackage->setWriteEven(Utils::makeEvent(newClientPackage->getBase(), fileDescriptor,
                                                        newClientPackage, onWrite, EV_WRITE | EV_PERSIST));

        newClientPackage->activateReadEvent();
    }
    catch(const exception& ex)
    {
        LOG(ERROR) << __func__ << " : " << ex.what();
    }
}

void TcpServer::onRead(evutil_socket_t fileDescriptor, short flags, void* arg)
{
    ClientPackage* clientPackage = nullptr;

    try
    {
        if(arg == nullptr)
            throw runtime_error("arg is null");

        clientPackage = (ClientPackage*)arg;

        ssize_t bytes = 0;
        uint8_t buff[READ_BUFF_SIZE] = { 0 };
        while(true)
        {
            bytes = read(fileDescriptor, buff, READ_BUFF_SIZE);
            if(bytes == 0)
                throw ClientException("client disconnected!");

            if(bytes < 0)
            {
                if(errno == EINTR)
                    continue;

                throw ClientException(" read() failed, errno = " +to_string(errno));
            }

            break;
        }

        clientPackage->setRequest(reinterpret_cast<char *>(buff));

        LOG(INFO) << "Read: " << clientPackage->getRequest();

        PackagesQueue::getInstance()->pushCommand(clientPackage);
    }
    catch (const ClientException& ex)
    {
        LOG(ERROR) << __func__ << " : " << ex.what();
        delete clientPackage;
    }
    catch(const exception& ex)
    {
        LOG(ERROR) << __func__ << " : " << ex.what();
    }
}

void TcpServer::onWrite(evutil_socket_t fd, short flags, void* arg)
{
    ClientPackage* clientPackage = nullptr;

    try
    {
        if(arg == nullptr)
            throw runtime_error("arg is null");

        clientPackage = (ClientPackage*)arg;
        LOG(INFO) << "onWrite: " << clientPackage->getResponse();
        ssize_t bytes;
        while(true)
        {
            bytes = write(fd, clientPackage->getResponse().c_str(), clientPackage->getResponse().length());
            if(bytes <= 0)
            {
                if(errno == EINTR)
                    continue;

                throw ClientException("write() failed, errno = " + to_string(errno) + " closing connection.");
            }

            break;
        }

        clientPackage->deactivateWriteEvent();
    }
    catch (const ClientException& ex)
    {
        LOG(ERROR) << __func__ << " : " << ex.what();
        delete clientPackage;
    }
    catch(const exception& ex)
    {
        LOG(ERROR) << __func__ << " : " << ex.what();
    }
}