//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_UNSUPPORTEDCOMMANDHANDLER_H
#define COMMANDSSERVICE_UNSUPPORTEDCOMMANDHANDLER_H

#include "ICommandHandler.h"

/**
 * @class UnsupportedCommandHandler
 * @brief Class is using to handle all commands which is not supporting.
 */

class UnsupportedCommandHandler : public ICommandHandler
{
public:

    /**
     * @brief Returns error message as response
     * @param command
     * @param result  output parameter
     */
    void handle(const Command& command, std::string& result) override;
};


#endif //COMMANDSSERVICE_UNSUPPORTEDCOMMANDHANDLER_H
