//
// Created by andrii on 29.08.21.
//

#include "CommandsHandlerFactory.h"
#include "PingHandler.h"
#include "UnsupportedCommandHandler.h"
#include "SumHandler.h"
#include "CatHandler.h"
#include "DataReaders/DataReader.h"

using namespace std;

namespace SupportedCommands
{
    const string PING = "ping";
    const string CAT = "cat";
    const string SUM = "sum";
}

ICommandHandler::Ptr CommandsHandlerFactory::getHandler(const string& command)
{
    scoped_lock(_mutex);

    if(command == SupportedCommands::PING)
    {
        return make_shared<PingHandler>();
    }
    else if(command== SupportedCommands::CAT)
    {
        return make_shared<CatHandler>(make_shared<DataReader>());
    }
    else if(command == SupportedCommands::SUM)
    {
        return make_shared<SumHandler>();
    }
    else
    {
        return make_shared<UnsupportedCommandHandler>();
    }
}