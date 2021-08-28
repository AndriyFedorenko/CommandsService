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

class TcpServer {
public:
    TcpServer(const std::string& address, const int port);
    ~TcpServer();

    void run();

private:
    void connect(const int connectionNum);
    void processCommands() const;

    static EventBasePtr makeEventBase();
    static EventPtr makeEvent(
            EventBasePtr base,
            evutil_socket_t fileDescriptor,
            void *callbackArg,
            event_callback_fn eventFunc,
            short events);
    static void onAccept(evutil_socket_t listen_sock, short flags, void* arg);
    static void onRead(evutil_socket_t fileDescriptor, short flags, void* arg);
    static void onWrite(evutil_socket_t fd, short flags, void* arg);

    const std::string _address;
    const int _port;
    ServerConnection _serverConnection;
};


#endif //COMMANDSSERVICE_TCPSERVER_H
