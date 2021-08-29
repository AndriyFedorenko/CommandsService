//
// Created by andrii on 27.08.21.
//

#ifndef COMMANDSSERVICE_SERVERAPPLICATION_H
#define COMMANDSSERVICE_SERVERAPPLICATION_H

#include "TcpServer.h"

class ServerApplication {
public:
    ServerApplication();
    void run(int argc, char **argv);
private:
    void main(int argc, char **argv);

    IServer::Ptr _server;
};


#endif //COMMANDSSERVICE_SERVERAPPLICATION_H
