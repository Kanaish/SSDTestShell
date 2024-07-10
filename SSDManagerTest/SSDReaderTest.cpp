/* Copyright 2024 Code Love you */

#include <stdexcept>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/FileManager.h"
#include "../SSDManager/SSDReader.cpp"

static const std::string RESULT_NAME_PATH = "test_result.txt";
static const std::string NAND_NAME_PATH = "test_nand.txt";

class FileManagerReaderMock : public FileManagerInterface {
 public:
    MOCK_METHOD(std::string, read, (std::string, int), (override));
    MOCK_METHOD(bool, write, (std::string, int, std::string), (override));
    MOCK_METHOD(bool, write, (std::string, std::string), (override));
};

class SSDReaderFileManagerMockFixture: public testing::Test {
 public:
    testing::NiceMock<FileManagerReaderMock> mock;
    std::string value = "0x12345678";
    std::string nand_file = NAND_NAME_PATH;
    std::string result_file = RESULT_NAME_PATH;
};

TEST_F(SSDReaderFileManagerMockFixture, FileManagerReaderMockReadTest) {
    std::string result;
    int index = 0;

    EXPECT_CALL(mock, read(nand_file, index))
        .WillRepeatedly(testing::Return(std::string(value)));

    result = mock.read(nand_file, index);

    EXPECT_EQ(result, value);
}

TEST_F(SSDReaderFileManagerMockFixture, FileManagerReaderMockWriteTest) {
    bool result;

    std::string result_file = RESULT_NAME_PATH;

    EXPECT_CALL(mock, write(result_file, value))
        .WillRepeatedly(testing::Return(true));

    result = mock.write(result_file, value);

    EXPECT_EQ(result, true);
}

TEST_F(SSDReaderFileManagerMockFixture, NormalReadTestWithMock) {
    bool result;
    int index = 0;


    EXPECT_CALL(mock, read(nand_file, index))
        .Times(1)
        .WillOnce(testing::Return(std::string(value)));

    EXPECT_CALL(mock, write(result_file, value))
        .Times(1)
        .WillOnce(testing::Return(true));

    SSDReader reader{ &mock };
    result = reader.read(nand_file, result_file, index);
    EXPECT_THAT(result, testing::Eq(true));
}

TEST_F(SSDReaderFileManagerMockFixture, ExceptionReadWithMock) {
    bool result;
    int index = 0;

    EXPECT_CALL(mock, read(nand_file, index))
        .WillRepeatedly(testing::Throw(std::exception()));

    EXPECT_CALL(mock, write(result_file, value))
        .WillRepeatedly(testing::Return(true));

    SSDReader reader{ &mock };
    result = reader.read(nand_file, result_file, index);
    EXPECT_THAT(result, testing::Eq(false));
}

TEST_F(SSDReaderFileManagerMockFixture, ExceptionWriteWithMock) {
    bool result;
    int index = 0;

    EXPECT_CALL(mock, read(nand_file, index))
        .Times(1)
        .WillRepeatedly(testing::Return(std::string(value)));

    EXPECT_CALL(mock, write(result_file, value))
        .Times(1)
        .WillOnce(testing::Throw(std::exception()));

    SSDReader reader{ &mock };
    result = reader.read(nand_file, result_file, index);
    EXPECT_THAT(result, testing::Eq(false));
}


TEST(SSDReaderTest, NormalReadTest) {
    FileManager m;
    bool result;

    int index = 0;
    std::string nand_file = NAND_NAME_PATH;
    std::string result_file = RESULT_NAME_PATH;

    SSDReader reader{ &m };
    result = reader.read(nand_file, result_file, index);

    EXPECT_THAT(result, testing::Eq(true));
}







