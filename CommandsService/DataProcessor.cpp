//
// Created by andrii on 29.08.21.
//

#include <thread>
#include <chrono>

#include <glog/logging.h>

#include "DataProcessor.h"
#include "PackagesQueue.h"
#include "Utils.h"

using namespace std;

namespace
{
    const int WAIT_NEW_MESS_MILLISEC = 10;
}

DataProcessor::DataProcessor(IHandlerFactory::Ptr handlerFactory, const int numOfThreads) :
_handlerFactory(handlerFactory),
_numOfThreads(numOfThreads)
{
}

void DataProcessor::process()
{
    for(int i = 0; i < _numOfThreads; i++)
        createThreadProcessor();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void DataProcessor::createThreadProcessor() const
{
    thread my_t([&]()
                {
                    while(true)
                    {
                        PackagesQueue *pq = PackagesQueue::getInstance();

                        ClientPackage *clientPackage = pq->popCommand();

                        if(clientPackage != nullptr)
                        {
                            try
                            {
                                Command cmd = Utils::parseCommand(clientPackage->getRequest());

                                string response;
                                ICommandHandler::Ptr handler = _handlerFactory->getHandler(cmd.command);
                                handler->handle(cmd, response);

                                clientPackage->setResponse(response);
                                clientPackage->activateWriteEvent();
                            }
                            catch(const std::exception& ex)
                            {
                                LOG(ERROR) << ex.what();
                            }
                        }
                        else
                        {
                            this_thread::sleep_for(chrono::milliseconds(WAIT_NEW_MESS_MILLISEC));
                        }
                    }
                });

    if(my_t.joinable())
        my_t.detach();
}
#pragma clang diagnostic pop
