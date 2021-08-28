//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_ICOMMANDHANDLER_H
#define COMMANDSSERVICE_ICOMMANDHANDLER_H

#include <string>

class ICommandHandler
{
public:
    using Ptr = std::shared_ptr<ICommandHandler>;

    virtual std::string handle(const std::string command) = 0;
};
#endif //COMMANDSSERVICE_ICOMMANDHANDLER_H
