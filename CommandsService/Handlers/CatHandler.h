//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_CATHANDLER_H
#define COMMANDSSERVICE_CATHANDLER_H

#include "ICommandHandler.h"

class CatHandler : public ICommandHandler
{
public:
    void handle(const Command& command, std::string& result) override;
};


#endif //COMMANDSSERVICE_CATHANDLER_H
