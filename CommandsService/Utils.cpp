//
// Created by andrii on 29.08.21.
//

#include "Utils.h"
#include <sstream>

using namespace std;

namespace
{
    const string COMMAND_SEPARATOR = " ";
}

Command Utils::parseCommand(const string& strCommand)
{
    Command cmd;
    istringstream iss(strCommand);
    iss >> cmd.command;

    for (string arg; iss >> arg;)
        cmd.arguments.emplace_back(arg);

    return cmd;
}

void Utils::buildResponse(const char status, const string& data, string& response)
{
    response = status;
    response += " ";
    response += data;
    response += "\n";
}

EventBasePtr Utils::makeEventBase()
{
    EventBasePtr base(event_base_new(), event_base_free);

    if(base == nullptr)
        throw runtime_error("event_base_new() failed");

    return base;
}

EventPtr Utils::makeEvent(EventBasePtr base,
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