//
// Created by andrii on 27.08.21.
//

#ifndef COMMANDSSERVICE_SERVERAPPLICATION_H
#define COMMANDSSERVICE_SERVERAPPLICATION_H

#include "TcpServer.h"

/**
 * @class ServerApplication
 * @brief This class demonizes application and creates TCP server.
 */

class ServerApplication {
public:
    ServerApplication();

    /**
     * This method runs application as daemon.
     *
     * @param argc: pass from main function
     * @param argv: pass from main function
     */
    void run(int argc, char **argv);
private:

    /**
     * This method creates and runs server and creates all dependencies for server.
     *
     * @param argc: pass from main function
     * @param argv: pass from main function
     */
    void main(int argc, char **argv);

    IServer::Ptr _server;
};


#endif //COMMANDSSERVICE_SERVERAPPLICATION_H
