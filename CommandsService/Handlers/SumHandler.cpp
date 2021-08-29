//
// Created by andrii on 29.08.21.
//

#include <exception>

#include "SumHandler.h"
#include "../Utils.h"

using namespace std;

namespace
{
    const string ERROR = "Invalid argument.";
}

void SumHandler::handle(const Command& command, string& result)
{
    long long sum = 0;

    try
    {
        for (auto arg : command.arguments)
        {
            sum += stoll(arg);
        }

        Utils::buildResponse(static_cast<char>(CommandStatus::SUCCESSFUL), to_string(sum), result);
    }
    catch (const exception ex)
    {
        Utils::buildResponse(static_cast<char>(CommandStatus::UNSUCCESSFUL), ERROR, result);
    }

}