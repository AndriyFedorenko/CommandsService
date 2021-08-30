//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_SERVERCONNECTION_H
#define COMMANDSSERVICE_SERVERCONNECTION_H

#include "ClientPackage.h"

/**
 * @brief This structure contains information about server connection needed for libevent
 */
struct ServerConnection
{
    evutil_socket_t fileDescriptor;
    EventBasePtr base;
    EventPtr acceptEvent;
};

#endif //COMMANDSSERVICE_SERVERCONNECTION_H
