cmake_minimum_required(VERSION 3.20)
project(CommandsService)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

find_package (glog 0.6.0 REQUIRED)

add_executable(CommandsService main.cpp ServerApplication.cpp ServerApplication.h TcpServer.cpp TcpServer.h ServerConnection.h ClientPackage.h PackagesQueue.cpp PackagesQueue.h Handlers/IHandlerFactory.h Handlers/ICommandHandler.h IServer.h ClientException.h Handlers/PingHandler.cpp Handlers/PingHandler.h Handlers/CommandsHandlerFactory.cpp Handlers/CommandsHandlerFactory.h Handlers/UnsupportedCommandHandler.cpp Handlers/UnsupportedCommandHandler.h Utils.cpp Utils.h Handlers/CatHandler.cpp Handlers/CatHandler.h Handlers/SumHandler.cpp Handlers/SumHandler.h Command.h IDataProcessor.h DataProcessor.cpp DataProcessor.h ClientPackage.cpp)

target_link_libraries(CommandsService libevent.a)
target_link_libraries(CommandsService libevent_pthreads.a)
target_link_libraries(CommandsService pthread)

target_link_libraries (CommandsService glog::glog)
