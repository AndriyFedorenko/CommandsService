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

/**
 * @class PackagesQueue
 * @brief This class is singleton. It is implementing clients message queue.
 * This class is thread safe. Messages are pushed into queue and remove after processing.
 */

class PackagesQueue
{
public:

    /**
     * This method is thread safe.
     *
     * @return PackagesQueue instance (one instance for application)
     */
    static PackagesQueue* getInstance();

    /**
     * This method is thread safe and adds message to queue.
     *
     * @param package: received client package
     */
    void pushCommand(ClientPackage * package);

    /**
     * This method is thread safe. It removes and return client message.
     *
     * @return client package
     */
    ClientPackage*  popCommand();

private:
    PackagesQueue()= default;
    ~PackagesQueue()= default;
    PackagesQueue(const PackagesQueue&) = delete;
    PackagesQueue& operator=(PackagesQueue&) = delete;

    /**
     * This method creates PackagesQueue. Is is using for once_flag to make singleton thread safe.
     *
     * @return PackagesQueue instance
     */
    static PackagesQueue* initInstance();

    static PackagesQueue* _instance;
    static std::once_flag _oneInstanceFlag;

    std::mutex _mutex;
    std::queue<ClientPackage*> _packagesQueue;
};


#endif //COMMANDSSERVICE_PACKAGESQUEUE_H
