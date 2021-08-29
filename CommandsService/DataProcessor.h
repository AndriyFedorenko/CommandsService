//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_DATAPROCESSOR_H
#define COMMANDSSERVICE_DATAPROCESSOR_H

#include "IDataProcessor.h"
#include "Handlers/IHandlerFactory.h"

class DataProcessor : public  IDataProcessor
{
public:
    DataProcessor(IHandlerFactory::Ptr handlerFactory, const int numOfThreads);

    virtual void process() override;
private:
    void createThreadProcessor() const;

    IHandlerFactory::Ptr _handlerFactory;
    const int _numOfThreads;
};


#endif //COMMANDSSERVICE_DATAPROCESSOR_H
