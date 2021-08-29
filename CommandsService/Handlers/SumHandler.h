//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_SUMHANDLER_H
#define COMMANDSSERVICE_SUMHANDLER_H

#include "ICommandHandler.h"

class SumHandler : public ICommandHandler
{
public:
    void handle(const Command& command, std::string& result) override;
};

#endif //COMMANDSSERVICE_SUMHANDLER_H
