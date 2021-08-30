//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_COMMAND_H
#define COMMANDSSERVICE_COMMAND_H

#include <string>
#include <list>

/**
 * @brief Structure is using for storing parsed commands
 */

struct Command
{
    std::string command;
    std::list<std::string> arguments;
};

#endif //COMMANDSSERVICE_COMMAND_H
