//
// Created by andrii on 29.08.21.
//

#include "CatHandler.h"

using namespace std;

namespace
{
    const string ERROR_MESSAGE = "File not found.";
}


void CatHandler::handle(const Command& command, std::string& result)
{
    // TODO validate command
    result = ERROR_MESSAGE;
}