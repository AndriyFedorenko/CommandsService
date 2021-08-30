//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_SUMHANDLER_H
#define COMMANDSSERVICE_SUMHANDLER_H

#include "ICommandHandler.h"

/**
 * @class SumHandler
 * @brief Class handles sum command.
 */

class SumHandler : public ICommandHandler
{
public:
    /**
     * @brief sums all parameters if parameters are numbers if not reruns error message
     * @param command
     * @param result
     */
    void handle(const Command& command, std::string& result) override;
};

#endif //COMMANDSSERVICE_SUMHANDLER_H
