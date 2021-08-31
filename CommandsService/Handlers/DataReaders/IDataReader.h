//
// Created by andrii on 31.08.21.
//

#ifndef COMMANDSSERVICE_IDATAREADER_H
#define COMMANDSSERVICE_IDATAREADER_H

#include <memory>
#include <string>

class IDataReader
{
public:
    using Ptr = std::shared_ptr<IDataReader>;

    virtual bool read(const std::string& source, std::string& data) = 0;
    virtual ~IDataReader() {}
};

#endif //COMMANDSSERVICE_IDATAREADER_H
