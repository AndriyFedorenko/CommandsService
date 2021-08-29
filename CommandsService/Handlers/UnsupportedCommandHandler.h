//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_UNSUPPORTEDCOMMANDHANDLER_H
#define COMMANDSSERVICE_UNSUPPORTEDCOMMANDHANDLER_H

#include "ICommandHandler.h"

class UnsupportedCommandHandler : public ICommandHandler
{
public:
    void handle(const Command& command, std::string& result) override;
};


#endif //COMMANDSSERVICE_UNSUPPORTEDCOMMANDHANDLER_H
