//
// Created by andrii on 29.08.21.
//

#include <exception>
#include <glog/logging.h>

#include "ClientPackage.h"

using namespace std;

ClientPackage::ClientPackage(
        evutil_socket_t fileDescriptor,
        EventBasePtr base):
        _fileDescriptor(fileDescriptor),
        _base(base)
{
    if (evutil_make_socket_nonblocking(_fileDescriptor) < 0)
        throw runtime_error("evutil_make_socket_nonblocking() failed");
}

ClientPackage::~ClientPackage()
{
    close(_fileDescriptor);
}

void ClientPackage::activateReadEvent()
{
    if (event_add(_readEvent.get(), NULL) < 0)
        throw runtime_error("event_add(read_event, ...) failed");
}

void ClientPackage::activateWriteEvent()
{
    if (event_add(_writeEvent.get(), NULL) < 0)
        throw runtime_error("event_add(peer->write_event, ...) failed");
}

void ClientPackage::deactivateWriteEvent()
{
    if(event_del(_writeEvent.get()) < 0)
        throw runtime_error("event_del() failed");
}

std::string& ClientPackage::getRequest()
{
    return _request;
}

void ClientPackage::setRequest(const std::string& request)
{
    _request = request;
}

std::string& ClientPackage::getResponse()
{
    return _response;
}
void ClientPackage::setResponse(const std::string& response)
{
    _response = response;
}

void ClientPackage::setReadEven(EventPtr readEvent)
{
    _readEvent = readEvent;
}

void ClientPackage::setWriteEven(EventPtr writeEvent)
{
    _writeEvent = writeEvent;
}

EventBasePtr ClientPackage::getBase()
{
    return _base;
}