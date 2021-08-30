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
    /**
     *
     * This function is using for parsing raw string command to Command object.
     *
     * @param strCommand: string command received from client
     * @return: Command object
     */
    Command parseCommand(const std::string& strCommand);

    /**
     * This function is using for building client response.
     *
     * @param status: status after processing
     * @param data: command processing results
     * @param response: it is output parameter for built response.
     */
    void buildResponse(const char status, const std::string& data, std::string& response);

    /**
     * This is wrapper for event_base_new.
     *
     * @return: RAII object for base event.
     */
    EventBasePtr makeEventBase();

    /**
     * This is wrapper for event_new.
     *
     * @param base
     * @param fileDescriptor
     * @param callbackArg
     * @param eventFunc
     * @param events
     * @return: RAII object for event.
     */
    EventPtr makeEvent(EventBasePtr base,
                             evutil_socket_t fileDescriptor,
                             void *callbackArg,
                             event_callback_fn eventFunc,
                             short events);
};

#endif //COMMANDSSERVICE_UTILS_H
