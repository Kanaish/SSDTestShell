/* Copyright 2024 Code Love you */

#include <stdexcept>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/SSDReader.cpp"
#include "../SSDManager/FileManager.h"

static const std::string RESULT_NAME_PATH = "result.txt";
static const std::string NAND_NAME_PATH = "nand.txt";

class FileManagerReaderMock : public FileManagerInterface {
 public:
    MOCK_METHOD(bool, init, (std::string), (override));
    MOCK_METHOD(bool, open, (std::string), (override));
    MOCK_METHOD(bool, close, (std::string), (override));

    MOCK_METHOD(std::string, read, (std::string, int), (override));
    MOCK_METHOD(bool, write, (std::string, int, std::string), (override));
    MOCK_METHOD(bool, write, (std::string, std::string), (override));
};

TEST(SSDReaderTest, FileManagerReaderMockReadTest) {
    testing::NiceMock<FileManagerReaderMock> mock;
    std::string value = "0x12345678";
    std::string result;
    int index = 0;
    std::string nand_file = NAND_NAME_PATH;

    EXPECT_CALL(mock, read(nand_file, index))
        .WillRepeatedly(testing::Return(std::string(value)));

    result = mock.read(nand_file, index);

    EXPECT_EQ(result, value);
}

TEST(SSDReaderTest, FileManagerReaderMockWriteTest) {
    testing::NiceMock<FileManagerReaderMock> mock;
    std::string value = "0x12345678";
    bool result;
    int index = 0;
    std::string result_file = RESULT_NAME_PATH;

    EXPECT_CALL(mock, write(result_file, value))
        .WillRepeatedly(testing::Return(true));

    result = mock.write(result_file, value);

    EXPECT_EQ(result, true);
}

TEST(SSDReaderTest, NormalReadTestWithMock) {
    testing::NiceMock<FileManagerReaderMock> mock;

    std::string value = "0x12345678";
    bool result;
    int index = 0;
    std::string nand_file = NAND_NAME_PATH;
    std::string result_file = RESULT_NAME_PATH;

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

TEST(SSDReaderTest, ExceptionReadWithMock) {
    testing::NiceMock<FileManagerReaderMock> mock;
    std::string value = "0x12345678";
    bool result;
    int index = 0;
    std::string nand_file = NAND_NAME_PATH;
    std::string result_file = RESULT_NAME_PATH;

    EXPECT_CALL(mock, read(nand_file, index))
        .WillRepeatedly(testing::Throw(std::exception()));

    EXPECT_CALL(mock, write(result_file, value))
        .WillRepeatedly(testing::Return(true));

    SSDReader reader{ &mock };
    result = reader.read(nand_file, result_file, index);
    EXPECT_THAT(result, testing::Eq(false));
}

TEST(SSDReaderTest, ExceptionWriteWithMock) {
    testing::NiceMock<FileManagerReaderMock> mock;
    std::string value = "0x12345678";
    bool result;

    int index = 0;
    std::string nand_file = NAND_NAME_PATH;
    std::string result_file = RESULT_NAME_PATH;

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

#if 0
TEST(SSDReaderTest, NormalReadTest) {
    FileManager m;
    unsigned int value = 0;
    bool result;

    int index = 0;
    std::string nand_file = NAND_NAME_PATH;
    std::string result_file = RESULT_NAME_PATH;

    SSDReader reader{ &m };
    result = reader.read(nand_file, result_file, index);

    EXPECT_THAT(result, testing::Eq(true));
}
#endif






