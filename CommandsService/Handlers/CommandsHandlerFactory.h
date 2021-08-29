//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_COMMANDSHANDLERFACTORY_H
#define COMMANDSSERVICE_COMMANDSHANDLERFACTORY_H

#include <mutex>

#include "IHandlerFactory.h"

class CommandsHandlerFactory : public IHandlerFactory
{
public:
    ICommandHandler::Ptr getHandler(const std::string& command) override;

private:
    std::mutex _mutex;
};


#endif //COMMANDSSERVICE_COMMANDSHANDLERFACTORY_H
