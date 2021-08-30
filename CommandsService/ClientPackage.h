//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_CLIENTPACKAGE_H
#define COMMANDSSERVICE_CLIENTPACKAGE_H

#include "Utils.h"

/**
 * @class ClientPackage
 * @brief Class is using to store all information about client and clients requests/response.
 * It implements method for working with client data and events. All received client packages are storing
 * in global PackageQueue.
 */

class ClientPackage
{
public:
    ClientPackage(
            evutil_socket_t fileDescriptor,
            EventBasePtr base);
    ~ClientPackage();

    /**
     * @brief This method wraps up event_add and add read event for client
     */
    void activateReadEvent();

    /**
     * @brief This method wraps up event_add and add write event for client
     */
    void activateWriteEvent();

    /**
     * @brief This method wraps up event_del and delete write event for client
     */
    void deactivateWriteEvent();

    /**
     * @brief getter for client message
     * @return clients message
     */
    std::string& getRequest();

    /**
     * @brief Set raw string format client message
     * @param request: clients message
     */
    void setRequest(const std::string& request);

    /**
     *  @brief getter for client response message
     * @return client response
     */
    std::string& getResponse();

    /**
     * @brief Set client response
     * @param response
     */
    void setResponse(const std::string& response);

    /**
     * @brief set read client envent
     * @param readEvent
     */
    void setReadEven(EventPtr readEvent);

    /**
     * set write client event
     * @param writeEvent
     */
    void setWriteEven(EventPtr writeEvent);

    /**
     * getter for base event
     * @return
     */
    EventBasePtr getBase();

private:
    evutil_socket_t _fileDescriptor;
    EventBasePtr _base;
    EventPtr _readEvent;
    EventPtr _writeEvent;

    std::string _request;
    std::string _response;
};

#endif //COMMANDSSERVICE_CLIENTPACKAGE_H
