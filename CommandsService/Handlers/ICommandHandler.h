//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_ICOMMANDHANDLER_H
#define COMMANDSSERVICE_ICOMMANDHANDLER_H

#include <string>
#include <memory>

#include "../Command.h"

class ICommandHandler
{
public:
    enum class CommandStatus : char
    {
        SUCCESSFUL = 'S',
        UNSUCCESSFUL = 'E'
    };

    using Ptr = std::shared_ptr<ICommandHandler>;

    ICommandHandler() {}
    virtual ~ICommandHandler() {}
    virtual void handle(const Command& Command, std::string& result) = 0;
};
#endif //COMMANDSSERVICE_ICOMMANDHANDLER_H
