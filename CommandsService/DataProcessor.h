//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_DATAPROCESSOR_H
#define COMMANDSSERVICE_DATAPROCESSOR_H

#include "IDataProcessor.h"
#include "Handlers/IHandlerFactory.h"

/**
 * @class DataProcessor
 * @brief This class implements IDataProcessor interface.
 * This class is processing commands simultaneously. It is using HandlerFactory to handle different commands.
 *
 */

class DataProcessor : public  IDataProcessor
{
public:
    /**
     * Constructor
     *
     * @param handlerFactory: Handler factory is providing handlers for command processing.
     * @param numOfThreads: How many threads should be created
     */
    DataProcessor(IHandlerFactory::Ptr handlerFactory, const int numOfThreads);

    /**
     * @brief Method runs command processing flow
     */
    virtual void process() override;
private:

    /**
     * @brief Method creates thread for getting command from queue and parsing it.
     * This method is using HandlerFactory to get specific handlers for processing command.
     */
    void createThreadProcessor() const;

    IHandlerFactory::Ptr _handlerFactory;
    const int _numOfThreads;
};


#endif //COMMANDSSERVICE_DATAPROCESSOR_H
