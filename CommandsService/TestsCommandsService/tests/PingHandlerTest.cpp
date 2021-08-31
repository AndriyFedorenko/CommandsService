//
// Created by andrii on 31.08.21.
//

#include <gtest/gtest.h>
#include <string>
#include <PingHandler.h>

class PingHandlerTest : public testing::Test
{
protected:
     void SetUp() override
     {
         _ping = std::make_shared<PingHandler>();
     }

      ICommandHandler::Ptr _ping;
};

TEST_F(PingHandlerTest, RunPingSuccessful)
{
    Command cmd;
    cmd.command = "ping";
    std::string response;
    _ping->handle(cmd, response);
    EXPECT_EQ(response, "S pong\n");
}

TEST_F(PingHandlerTest, RunPingUnsuccessful)
{
    Command cmd;
    cmd.command = "ping";
    cmd.arguments.push_back("test");
    std::string response;
    _ping->handle(cmd, response);
    EXPECT_EQ(response, "E Unable to process your request\n");
}
