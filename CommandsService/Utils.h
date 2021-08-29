//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_UTILS_H
#define COMMANDSSERVICE_UTILS_H

#include <string>
#include <memory>
#include <event.h>
#include <unistd.h>

#include "Command.h"

using EventBasePtr = std::shared_ptr<event_base>;
using EventPtr = std::shared_ptr<event>;

namespace Utils
{
    Command parseCommand(const std::string& strCommand);
    void buildResponse(const char status, const std::string& data, std::string& response);

    EventBasePtr makeEventBase();
    EventPtr makeEvent(EventBasePtr base,
                             evutil_socket_t fileDescriptor,
                             void *callbackArg,
                             event_callback_fn eventFunc,
                             short events);
};

#endif //COMMANDSSERVICE_UTILS_H
