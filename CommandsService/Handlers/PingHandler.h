//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_PINGHANDLER_H
#define COMMANDSSERVICE_PINGHANDLER_H

#include "ICommandHandler.h"

class PingHandler : public ICommandHandler
{
public:
    void handle(const Command& command, std::string& result) override;
};


#endif //COMMANDSSERVICE_PINGHANDLER_H
