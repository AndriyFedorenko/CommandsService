//
// Created by andrii on 27.08.21.
//

#include <regex>
#include <string>
#include <iostream>

#include <unistd.h>
#include <glog/logging.h>
#include <sys/stat.h>

#include "ServerApplication.h"
#include "DataProcessor.h"
#include "Handlers/CommandsHandlerFactory.h"


using namespace std;

namespace
{
    const unsigned short NUM_REQUIRED_ARG = 4;
    const string IPV4_VALIDATION = "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
    const string NUM_VALIDATION = "[0-9]+";
}

ServerApplication::ServerApplication():
_server(nullptr)
{

}

void ServerApplication::run(int argc, char **argv)
{
    google::InitGoogleLogging(argv[0]);

    pid_t pid, sid;
    pid = fork();

    if(pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    else if(pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    umask(0);

    LOG(INFO) << "Successfully started service";

    sid = setsid();
    if(sid < 0)
    {
        LOG(ERROR) << "Could not generate session ID for child process";
        exit(EXIT_FAILURE);
    }

    if((chdir("/")) < 0)
    {
        LOG(ERROR) << "Could not change working directory to /";
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    main(argc, argv);

    LOG(INFO) << "Stopping service";
    exit(EXIT_SUCCESS);
}

void ServerApplication::main(int argc, char **argv)
{
    if(argc < NUM_REQUIRED_ARG)
    {
        LOG(ERROR) << "Please specify <ip address> <port> <number of threads>" << endl;
        return;
    }

    regex ipv4_regex(IPV4_VALIDATION);
    string ip = argv[1];

    if (!regex_match(ip, ipv4_regex))
    {
        LOG(ERROR) << "Invalid ip address";
        return;
    }

    regex int_regex(NUM_VALIDATION);
    string port = argv[2];
    if (!regex_match(port, int_regex))
    {
        LOG(ERROR) << "Invalid port";
        return;
    }

    try
    {
        auto dataProcessor = make_shared<DataProcessor>(make_shared<CommandsHandlerFactory>(), stoi(argv[3]));
        _server = make_shared<TcpServer>(dataProcessor, ip, stoi(port));
        _server->run();
    }
    catch(const runtime_error& ex)
    {
        LOG(ERROR) << ex.what();
    }
    catch(const exception& ex)
    {
        LOG(ERROR) << ex.what();
    }
    catch(...)
    {
        LOG(ERROR) << "Error undefined";
    }
}