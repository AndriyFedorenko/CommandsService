//
// Created by andrii on 29.08.21.
//

#include "PingHandler.h"

using namespace std;

namespace
{
    const string DEFAULT_RESPONSE = "pong";
}


void PingHandler::handle(const Command& command, std::string& result)
{
    // TODO validate command
    result = DEFAULT_RESPONSE;
}
