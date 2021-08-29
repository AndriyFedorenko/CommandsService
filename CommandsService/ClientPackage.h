//
// Created by andrii on 28.08.21.
//

#ifndef COMMANDSSERVICE_CLIENTPACKAGE_H
#define COMMANDSSERVICE_CLIENTPACKAGE_H

#include "Utils.h"

class ClientPackage
{
public:
    ClientPackage(
            evutil_socket_t fileDescriptor,
            EventBasePtr base);
    ~ClientPackage();

    void activateReadEvent();
    void activateWriteEvent();
    void deactivateWriteEvent();

    std::string& getRequest();
    void setRequest(const std::string& request);

    std::string& getResponse();
    void setResponse(const std::string& response);

    void setReadEven(EventPtr readEvent);
    void setWriteEven(EventPtr writeEvent);

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
