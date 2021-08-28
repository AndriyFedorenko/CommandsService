cmake_minimum_required(VERSION 3.20)
project(CommandsService)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

add_executable(CommandsService main.cpp ServerApplication.cpp ServerApplication.h TcpServer.cpp TcpServer.h ServerConnection.h ClientPackage.h PackagesQueue.cpp PackagesQueue.h IHandlerFactory.h ICommandHandler.h)

target_link_libraries(CommandsService libevent.a)
target_link_libraries(CommandsService libevent_pthreads.a)
target_link_libraries(CommandsService pthread)
