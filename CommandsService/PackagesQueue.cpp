//
// Created by andrii on 28.08.21.
//

#include <mutex>

#include "PackagesQueue.h"

using namespace std;

PackagesQueue* PackagesQueue::_instance = nullptr;

PackagesQueue*  PackagesQueue::getInstance()
{
    if(_instance == nullptr)
        _instance = new PackagesQueue();

    return _instance;
}

PackagesQueue::PackagesQueue()
{
}

void PackagesQueue::pushReceivedCommand(ClientPackage * package)
{
    std::scoped_lock lock(_mutexWaiting);
    _waitingQueue.push(package);
}

ClientPackage*  PackagesQueue::popReadyCommand()
{
    std::scoped_lock lock(_mutexReady);

    if(_readyQueue.empty())
        return nullptr;

    ClientPackage* pack = _readyQueue.front();
    _readyQueue.pop();
    return pack;
}

void PackagesQueue::pushReadyCommand(ClientPackage * package)
{
    std::scoped_lock lock(_mutexReady);
    _readyQueue.push(package);
}

ClientPackage*  PackagesQueue::popReceivedCommand()
{
    std::scoped_lock lock(_mutexWaiting);

    if(_waitingQueue.empty())
        return nullptr;

    ClientPackage* pack = _waitingQueue.front();
    _waitingQueue.pop();
    return pack;
}