//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_ISERVER_H
#define COMMANDSSERVICE_ISERVER_H

#include <memory>

/**
 * @class IServer
 * @brief This class is implementing server interface. It is providing additional flexibility.
 * For instance we can add support for UDP protocol.
 *
 */

class IServer
{
public:
    using Ptr = std::shared_ptr<IServer>;

    IServer() = default;
    virtual ~IServer() {}
    virtual void run() = 0;
};

#endif //COMMANDSSERVICE_ISERVER_H
