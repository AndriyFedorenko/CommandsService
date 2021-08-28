#include <event.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <memory>
#include <string>

#include "TcpServer.h"

using namespace std;

int main(int argc, char **argv)
{
    TcpServer server("127.0.0.1", 8224);
    server.run();

    return 0;
}
