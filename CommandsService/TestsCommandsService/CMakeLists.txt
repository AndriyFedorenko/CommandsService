cmake_minimum_required(VERSION 3.20)
project(TestsCommandsService)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)
include_directories(../Handlers)

add_executable(TestsCommandsService main.cpp tests/PingHandlerTest.cpp ../Handlers/PingHandler.cpp ../Utils.cpp tests/SumHandlerTest.cpp ../Handlers/SumHandler.cpp tests/CatHandlerTest.cpp ../Handlers/CatHandler.cpp)
target_link_libraries(TestsCommandsService gtest gtest_main)
target_link_libraries(TestsCommandsService gmock gmock_main)
target_link_libraries(TestsCommandsService libevent.a)