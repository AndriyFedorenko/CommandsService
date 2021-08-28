//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_PACKAGESQUEUE_H
#define COMMANDSSERVICE_PACKAGESQUEUE_H

#include <mutex>
#include <queue>
#include <thread>

#include "IHandlerFactory.h"
#include "ClientPackage.h"

class PackagesQueue
{
public:
    PackagesQueue(const PackagesQueue&) = delete;
    PackagesQueue& operator=(PackagesQueue&) = delete;

    static PackagesQueue* getInstance();

    void pushReceivedCommand(ClientPackage * package);
    ClientPackage*  popReceivedCommand();

    void pushReadyCommand(ClientPackage * package);
    ClientPackage*  popReadyCommand();

private:
    PackagesQueue();

    static PackagesQueue* _instance;

    std::mutex _mutexWaiting;
    std::mutex _mutexReady;
    std::queue<ClientPackage*> _waitingQueue;
    std::queue<ClientPackage*> _readyQueue;
};


#endif //COMMANDSSERVICE_PACKAGESQUEUE_H
