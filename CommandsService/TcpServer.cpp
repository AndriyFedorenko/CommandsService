//
// Created by andrii on 27.08.21.
//

#include <thread>
#include <event.h>
#include <event2/thread.h>

#include "TcpServer.h"

using namespace std;


TcpServer::TcpServer(const std::string& address, const int port) :
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

    _serverConnection.base = makeEventBase();
    _serverConnection.acceptEvent = makeEvent(_serverConnection.base, _serverConnection.fileDescriptor,
                                              &_serverConnection, onAccept, EV_READ | EV_PERSIST);

    if(event_add(_serverConnection.acceptEvent.get(), NULL) < 0)
        throw runtime_error("event_add() failed");

    evthread_use_pthreads();

    processCommands();

    if(event_base_dispatch(_serverConnection.base.get()) < 0)
        throw runtime_error("event_base_dispatch() failed");
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void TcpServer::processCommands() const {
    thread my_t([&]()
    {
        while(true)
        {
            PackagesQueue *pq = PackagesQueue::getInstance();

            ClientPackage *clientPackage = pq->popReceivedCommand();

            if(clientPackage != nullptr)
            {
                // TODO process command

                pq->pushReadyCommand(clientPackage);

                if (event_add(clientPackage->writeEvent.get(), NULL) < 0)
                    cout << "event_add(peer->write_event, ...) failed" << endl;
            }
        }
    });

    if(my_t.joinable())
        my_t.detach();
}
#pragma clang diagnostic pop

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

EventBasePtr TcpServer::makeEventBase()
{
    EventBasePtr base(event_base_new(), event_base_free);

    if(base == nullptr)
        throw runtime_error("event_base_new() failed");

    return base;
}

EventPtr TcpServer::makeEvent(EventBasePtr base,
                                         evutil_socket_t fileDescriptor,
                                         void *callbackArg,
                                         event_callback_fn eventFunc,
                                         short events)
{
    EventPtr newEvent (event_new(base.get(), fileDescriptor,
                                                events, eventFunc, callbackArg), [] (event* e) {
        if(e != nullptr)
        {
            event_del(e);
            event_free(e);
        }
    });

    if(newEvent == nullptr)
        throw runtime_error("event_new() failed");

    return newEvent;
}

void TcpServer::onAccept(evutil_socket_t listen_sock, short flags, void* arg)
{
    if(arg == nullptr)
    {
        cout << "arg is null" <<endl;
        return;
    }

    try
    {
        ServerConnection *serverConn = (ServerConnection *) arg;
        evutil_socket_t fileDescriptor = accept(listen_sock, 0, 0);

        if (fileDescriptor < 0)
            throw runtime_error("accept() failed");

        if (evutil_make_socket_nonblocking(fileDescriptor) < 0)
            throw runtime_error("evutil_make_socket_nonblocking() failed");

        ClientPackage* newClientPackage = new ClientPackage();
        newClientPackage->base = serverConn->base;
        newClientPackage->fileDescriptor = fileDescriptor;
        newClientPackage->readEvent = makeEvent(newClientPackage->base, newClientPackage->fileDescriptor,newClientPackage, onRead, EV_READ | EV_PERSIST);
        newClientPackage->writeEvent = makeEvent(newClientPackage->base, newClientPackage->fileDescriptor,
                                                 newClientPackage, onWrite, EV_WRITE | EV_PERSIST);

        if (event_add(newClientPackage->readEvent.get(), NULL) < 0)
            throw runtime_error( "event_add(read_event, ...) failed");
    }
    catch(const exception& ex)
    {
        cout << __func__ << " : " << ex.what() << endl; // TODO add logger
    }
}

void TcpServer::onRead(evutil_socket_t fileDescriptor, short flags, void* arg)
{
    if(arg == nullptr)
    {
        cout << "arg is null" <<endl;
        return;
    }

    ClientPackage* clientPackage = (ClientPackage*)arg;

    ssize_t bytes = 0;
    uint8_t buff[READ_BUFF_SIZE] = { 0 };
    while(true)
    {
        bytes = read(fileDescriptor, buff, READ_BUFF_SIZE);
        if(bytes == 0)
        {
            cout << "client disconnected!" << endl;
            delete clientPackage;
            return;
        }

        if(bytes < 0)
        {
            if(errno == EINTR)
                continue;

            cout << " read() failed, errno = " <<  errno << endl;
            delete clientPackage;
            return;
        }

        break;
    }

    clientPackage->request =reinterpret_cast<char *>(buff);
    cout << "Read: " << clientPackage->request << endl; // TODO remove
    PackagesQueue::getInstance()->pushReceivedCommand(clientPackage);
}

void TcpServer::onWrite(evutil_socket_t fd, short flags, void* arg)
{
    if(arg == nullptr)
    {
        cout << "arg is null" <<endl;
        return;
    }

    ClientPackage* clientPackage = (ClientPackage*)arg;
    cout << "onWrite: " <<clientPackage->request << endl; // TODO remove
    ssize_t bytes;
    while(true)
    {
        bytes = write(fd, clientPackage->request.c_str(), clientPackage->request.length());
        if(bytes <= 0)
        {
            if(errno == EINTR)
                continue;

            cout << "write() failed, errno = "<< errno << " closing connection." << endl;
            delete clientPackage;
            return;
        }

        break;
    }

    if(event_del(clientPackage->writeEvent.get()) < 0)
       cout << "event_del() failed";
}