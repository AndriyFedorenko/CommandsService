//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_COMMANDSHANDLERFACTORY_H
#define COMMANDSSERVICE_COMMANDSHANDLERFACTORY_H

#include <mutex>

#include "IHandlerFactory.h"

/**
 * @class CommandsHandlerFactory
 * @brief Class is implementing commands handler factory. This factory is creating command handlers.
 */

class CommandsHandlerFactory : public IHandlerFactory
{
public:
    /**
     * @brief This method creates command handlers for each supported commands.
     * @param command: it is just command without arguments
     * @return
     */
    ICommandHandler::Ptr getHandler(const std::string& command) override;

private:
    std::mutex _mutex;
};


#endif //COMMANDSSERVICE_COMMANDSHANDLERFACTORY_H
