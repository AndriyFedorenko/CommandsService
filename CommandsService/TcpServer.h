//
// Created by andrii on 27.08.21.
//

#ifndef COMMANDSSERVICE_TCPSERVER_H
#define COMMANDSSERVICE_TCPSERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <memory>
#include <string>
#include <queue>

#include "ServerConnection.h"
#include "ClientPackage.h"
#include "PackagesQueue.h"
#include "IServer.h"
#include "IDataProcessor.h"

class TcpServer : public IServer
{
public:
    TcpServer(
            IDataProcessor::Ptr dataProcessor,
            const std::string& address,
            const int port);
    ~TcpServer();

    void run() override;

private:
    void connect(const int connectionNum);

    static void onAccept(evutil_socket_t listen_sock, short flags, void* arg);
    static void onRead(evutil_socket_t fileDescriptor, short flags, void* arg);
    static void onWrite(evutil_socket_t fd, short flags, void* arg);

    const std::string _address;
    const int _port;
    ServerConnection _serverConnection;
    IDataProcessor::Ptr _dataProcessor;
};


#endif //COMMANDSSERVICE_TCPSERVER_H
