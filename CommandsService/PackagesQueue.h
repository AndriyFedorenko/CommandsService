//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_PACKAGESQUEUE_H
#define COMMANDSSERVICE_PACKAGESQUEUE_H

#include <mutex>
#include <queue>
#include <thread>

#include "Handlers/IHandlerFactory.h"
#include "ClientPackage.h"

class PackagesQueue
{
public:
    static PackagesQueue* getInstance();

    void pushCommand(ClientPackage * package);
    ClientPackage*  popCommand();

    void pushReadyCommand(ClientPackage * package);
    ClientPackage*  popReadyCommand();

private:
    PackagesQueue()= default;
    ~PackagesQueue()= default;
    PackagesQueue(const PackagesQueue&) = delete;
    PackagesQueue& operator=(PackagesQueue&) = delete;

    static PackagesQueue* initInstance();

    static PackagesQueue* _instance;
    static std::once_flag _oneInstanceFlag;

    std::mutex _mutex;
    std::queue<ClientPackage*> _packagesQueue;
};


#endif //COMMANDSSERVICE_PACKAGESQUEUE_H
