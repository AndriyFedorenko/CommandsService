//
// Created by andrii on 29.08.21.
//

#ifndef COMMANDSSERVICE_CLIENTEXCEPTION_H
#define COMMANDSSERVICE_CLIENTEXCEPTION_H

#include <exception>

/**
 * @class ClientException
 * @brief Custom exception for handling client disconnect event
 */

class ClientException : public std::exception
{
    std::string _message;
public:
    ClientException(const std::string& message) : _message(message) {}

    const char * what() const noexcept override
    {
        return _message.c_str();
    }
};

#endif //COMMANDSSERVICE_CLIENTEXCEPTION_H
