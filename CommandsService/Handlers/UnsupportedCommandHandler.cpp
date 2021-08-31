//
// Created by andrii on 29.08.21.
//

#include "UnsupportedCommandHandler.h"

using namespace std;

void UnsupportedCommandHandler::handle(const Command& command, std::string& result)
{
    result = static_cast<char>(CommandStatus::UNSUCCESSFUL);
    result += " ";
    result += "This command is not supported.\n";
}
