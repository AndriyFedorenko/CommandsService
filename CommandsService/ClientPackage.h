//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_CLIENTPACKAGE_H
#define COMMANDSSERVICE_CLIENTPACKAGE_H

#include <event.h>
#include <unistd.h>

using EventBasePtr = std::shared_ptr<event_base>;
using EventPtr = std::shared_ptr<event>;

struct ClientPackage
{
    enum ProcessingStatus
    {
        RECEIVED = 0,
        INPROGRES,
        PROCESSED,
        WAITING
    };

    ClientPackage() : fileDescriptor(0) {}
    ~ClientPackage()
    {
        close(fileDescriptor);
    }
    evutil_socket_t fileDescriptor;
    EventBasePtr base;
    EventPtr readEvent;
    EventPtr writeEvent;

    std::string request;
    std::string response;
    // TODO ProcessingStatus status;
};

#endif //COMMANDSSERVICE_CLIENTPACKAGE_H
