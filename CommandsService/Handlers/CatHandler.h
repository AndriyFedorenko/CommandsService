//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_CATHANDLER_H
#define COMMANDSSERVICE_CATHANDLER_H

#include "ICommandHandler.h"
#include "DataReaders/IDataReader.h"


/**
 * @class CatHandler
 * @brief Class handles cat command.
 */

class CatHandler : public ICommandHandler
{
public:
    CatHandler(IDataReader::Ptr fileReader);


    /**
     * @brief If file exists then returns file contents if not return error.
     * @param command
     * @param result
     */
    void handle(const Command& command, std::string& result) override;

private:
    IDataReader::Ptr _fileReader;
};


#endif //COMMANDSSERVICE_CATHANDLER_H
