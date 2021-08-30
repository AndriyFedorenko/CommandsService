//
// Created by andrii on 29.08.21.
//

#include <fstream>
#include <streambuf>

#include "CatHandler.h"
#include "../Utils.h"

using namespace std;

namespace
{
    const string ERROR_MESS_FILE_NOT_FOUND = "File not found.";
    const string ERROR_MESS_INVALID_ARGS = "Invalid argument.";
}

void CatHandler::handle(const Command& command, std::string& result)
{
    CommandStatus status = CommandStatus::UNSUCCESSFUL;
    string data;

    if(!command.arguments.empty() || command.arguments.size() == 1)
    {
        std::ifstream file(command.arguments.front());
        if(file.good())
        {
            data.assign((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
            status = CommandStatus::SUCCESSFUL;
            file.close();
        }
        else
        {
            data = ERROR_MESS_FILE_NOT_FOUND;
        }
    }
    else
    {
        data = ERROR_MESS_INVALID_ARGS;
    }

    Utils::buildResponse(static_cast<char>(status), data, result);
}