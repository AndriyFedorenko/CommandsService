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

/**
 * @class TcpServer
 * @brief This class is implementing TCP server.
 * This class is wrapping up libevent functions and implementing asynchronous socket.
 * TCP server is receiving requests, processing requests by DataProcessor and sending responses to clients.
 *
 */

class TcpServer : public IServer
{
public:
    /**
     *
     * @param dataProcessor: It is IDataProcessor interface. Pass data processor
     * @param address: IP address
     * @param port
     */
    TcpServer(
            IDataProcessor::Ptr dataProcessor,
            const std::string& address,
            const int port);
    ~TcpServer();

    /**
     * This method starts server
     */
    void run() override;

private:

    /**
     * this method binds to and listens at a port to open it up for connections (this is a passive open).
     * @param connectionNum: Default value 1000
     */
    void connect(const int connectionNum);

    /**
     * It is libevent callback for accepting new connections
     * @param listen_sock
     * @param flags
     * @param arg
     */
    static void onAccept(evutil_socket_t listen_sock, short flags, void* arg);

    /**
     * It is libevent callback for receiving client messages
     * @param fileDescriptor
     * @param flags
     * @param arg
     */
    static void onRead(evutil_socket_t fileDescriptor, short flags, void* arg);

    /**
     * It is libevent callback for sending client messages
     * @param fd
     * @param flags
     * @param arg
     */
    static void onWrite(evutil_socket_t fileDescriptor, short flags, void* arg);

    const std::string _address;
    const int _port;
    ServerConnection _serverConnection;
    IDataProcessor::Ptr _dataProcessor;
};


#endif //COMMANDSSERVICE_TCPSERVER_H
