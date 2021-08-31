//
// Created by andrii on 31.08.21.
//

#include <gtest/gtest.h>
#include <string>
#include <SumHandler.h>

class SumHandlerTest : public testing::Test
{
protected:
    void SetUp() override
    {
        _sum = std::make_shared<SumHandler>();
    }

    ICommandHandler::Ptr _sum;
};

TEST_F(SumHandlerTest, RunSumSuccessful)
{
    Command cmd;
    cmd.command = "sum";
    cmd.arguments = {"3", "4", "8"};
    std::string response;
    _sum->handle(cmd, response);
    EXPECT_EQ(response, "S 15\n");
}

TEST_F(SumHandlerTest, RunSumUnsuccessful)
{
    Command cmd;
    cmd.command = "sum";
    cmd.arguments = {"3", "P", "8"};
    std::string response;
    _sum->handle(cmd, response);
    EXPECT_EQ(response, "E Invalid argument.\n");
}