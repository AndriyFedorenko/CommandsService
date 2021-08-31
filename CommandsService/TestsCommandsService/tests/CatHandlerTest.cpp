//
// Created by andrii on 31.08.21.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <CatHandler.h>
#include <DataReaders/IDataReader.h>

struct MockDataReader : IDataReader
{
    MOCK_METHOD(bool, read, (const std::string&, std::string&));

};

class CatHandlerTest : public testing::Test
{
protected:
    void SetUp() override
    {
        _dataReader = std::make_shared<MockDataReader>();
        _cat = std::make_shared<CatHandler>(_dataReader);
    }
    std::shared_ptr<MockDataReader> _dataReader;
    ICommandHandler::Ptr _cat;
};

TEST_F(CatHandlerTest, CatHandlerSuccessful)
{
    Command cmd;
    cmd.command = "cat";
    cmd.arguments = {"test"};
    std::string data;
    std::string response;
    EXPECT_CALL(*(_dataReader), read(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return(true));
    _cat->handle(cmd, response);
    EXPECT_EQ(response, "S \n");
}

TEST_F(CatHandlerTest, CatHandlerUnsuccessful)
{
    Command cmd;
    cmd.command = "cat";
    cmd.arguments = {"test"};
    std::string data;
    std::string response;
    EXPECT_CALL(*(_dataReader), read(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return(false));
    _cat->handle(cmd, response);
    EXPECT_EQ(response, "E File not found.\n");
}