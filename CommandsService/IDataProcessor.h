//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_IDATAPROCESSOR_H
#define COMMANDSSERVICE_IDATAPROCESSOR_H

#include <memory>

/**
 * @class IDataProcessor
 * @brief This class is implementing interface for data processor.
 */

class IDataProcessor
{
public:
    using Ptr = std::shared_ptr<IDataProcessor>;

    IDataProcessor() = default;
    virtual ~IDataProcessor() {}
    virtual void process() = 0;
};

#endif //COMMANDSSERVICE_IDATAPROCESSOR_H
