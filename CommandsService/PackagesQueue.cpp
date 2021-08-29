//
// Created by andrii on 28.08.21.
//

#include <mutex>

#include "PackagesQueue.h"

using namespace std;

PackagesQueue* PackagesQueue::_instance = nullptr;
std::once_flag PackagesQueue::_oneInstanceFlag;

PackagesQueue* PackagesQueue::initInstance()
{
    if(_instance == nullptr)
        _instance = new PackagesQueue();

    return _instance;
}

PackagesQueue* PackagesQueue::getInstance()
{
    call_once(_oneInstanceFlag, &PackagesQueue::initInstance);
    return _instance;
}

void PackagesQueue::pushCommand(ClientPackage * package)
{
    scoped_lock lock(_mutex);
    _packagesQueue.push(package);
}

ClientPackage*  PackagesQueue::popCommand()
{
    scoped_lock lock(_mutex);

    if(_packagesQueue.empty())
        return nullptr;

    ClientPackage* pack = _packagesQueue.front();
    _packagesQueue.pop();
    return pack;
}