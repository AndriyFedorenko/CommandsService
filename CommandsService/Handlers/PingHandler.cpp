//
// Created by andrii on 29.08.21.
//

#include "PingHandler.h"
#include "../Utils.h"

using namespace std;

namespace
{
    const string DEFAULT_RESPONSE = "pong";
    const string ERROR = "Unable to process your request";
}

void PingHandler::handle(const Command& command, std::string& result)
{
    if(command.arguments.empty())
    {
        Utils::buildResponse(static_cast<char>(CommandStatus::SUCCESSFUL), DEFAULT_RESPONSE, result);
    }
    else
    {
        Utils::buildResponse(static_cast<char>(CommandStatus::UNSUCCESSFUL), ERROR, result);
    }
}
