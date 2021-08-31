//
// Created by andrii on 29.08.21.
//

#include "CatHandler.h"
#include "../Utils.h"

using namespace std;

namespace
{
    const string ERROR_MESS_FILE_NOT_FOUND = "File not found.";
}

CatHandler::CatHandler(IDataReader::Ptr fileReader) : _fileReader(fileReader)
{
}

void CatHandler::handle(const Command& command, std::string& result)
{
    CommandStatus status = CommandStatus::SUCCESSFUL;
    string data;
    string fileName = command.arguments.empty() ? "" : command.arguments.front();
    if(!_fileReader->read(fileName, data))
    {
        data = ERROR_MESS_FILE_NOT_FOUND;
        status = CommandStatus::UNSUCCESSFUL;
    }

    Utils::buildResponse(static_cast<char>(status), data, result);
}
