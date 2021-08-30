//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_PINGHANDLER_H
#define COMMANDSSERVICE_PINGHANDLER_H

#include "ICommandHandler.h"

/**
 * @class PingHandler
 * @brief Class handles ping command.
 */

class PingHandler : public ICommandHandler
{
public:
    /**
     * @brief returns pong as response or error message if command has unsupported parameters
     * @param command
     * @param result
     */
    void handle(const Command& command, std::string& result) override;
};


#endif //COMMANDSSERVICE_PINGHANDLER_H
