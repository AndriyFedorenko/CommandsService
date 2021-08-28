//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_IHANDLERFACTORY_H
#define COMMANDSSERVICE_IHANDLERFACTORY_H

#include <memory>
#include <string>
#include "ICommandHandler.h"

class IHandlerFactory
{
public:
    using Ptr = std::shared_ptr<IHandlerFactory>;

    virtual ICommandHandler::Ptr getHendler(const std::string& command) = 0;
};

#endif //COMMANDSSERVICE_IHANDLERFACTORY_H
