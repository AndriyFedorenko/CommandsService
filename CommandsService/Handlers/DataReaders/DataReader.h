//
// Created by andrii on 31.08.21.
//

#ifndef COMMANDSSERVICE_DATAREADER_H
#define COMMANDSSERVICE_DATAREADER_H

#include "IDataReader.h"

class DataReader : public IDataReader
{
public:
    bool read(const std::string& source, std::string& data) override;
};


#endif //COMMANDSSERVICE_DATAREADER_H
