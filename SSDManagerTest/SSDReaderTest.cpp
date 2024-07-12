/* Copyright 2024 Code Love you */

#include <stdexcept>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/FileManager.h"
#include "../SSDManager/SSDReader.cpp"

using namespace std;
using namespace testing;

#define RESULT_NAME_PATH "test_result.txt";
#define NAND_NAME_PATH   "test_nand.txt";

class FileManagerReaderMock : public FileManagerInterface {
 public:
    MOCK_METHOD(string, read, (string name), (override));
    MOCK_METHOD(string, read, (string, int), (override));
    MOCK_METHOD(bool, write, (string, int, string), (override));
    MOCK_METHOD(bool, write, (string, string), (override));
};

class SSDReaderFileManagerMockFixture: public Test {
 public:
    NiceMock<FileManagerReaderMock> mock;
    string value = "0x12345678";
    string nand_file = NAND_NAME_PATH;
    string result_file = RESULT_NAME_PATH;
};

TEST_F(SSDReaderFileManagerMockFixture, FileManagerReaderMockReadTest) {
    string result;
    int index = 0;

    EXPECT_CALL(mock, read(nand_file, index))
        .WillRepeatedly(Return(string(value)));

    result = mock.read(nand_file, index);

    EXPECT_EQ(result, value);
}

TEST_F(SSDReaderFileManagerMockFixture, FileManagerReaderMockWriteTest) {
    bool result;

    string result_file = RESULT_NAME_PATH;

    EXPECT_CALL(mock, write(result_file, value))
        .WillRepeatedly(Return(true));

    result = mock.write(result_file, value);

    EXPECT_EQ(result, true);
}

TEST_F(SSDReaderFileManagerMockFixture, NormalReadTestWithMock) {
    bool result;
    int index = 0;


    EXPECT_CALL(mock, read(nand_file, index))
        .Times(1)
        .WillOnce(Return(string(value)));

    EXPECT_CALL(mock, write(result_file, value))
        .Times(1)
        .WillOnce(Return(true));

    SSDReader reader{ &mock };
    result = reader.read(nand_file, result_file, index);
    EXPECT_THAT(result, Eq(true));
}

TEST_F(SSDReaderFileManagerMockFixture, ExceptionReadWithMock) {
    bool result;
    int index = 0;

    EXPECT_CALL(mock, read(nand_file, index))
        .WillRepeatedly(Throw(exception()));

    EXPECT_CALL(mock, write(result_file, value))
        .WillRepeatedly(Return(true));

    SSDReader reader{ &mock };
    result = reader.read(nand_file, result_file, index);
    EXPECT_THAT(result, Eq(false));
}

TEST_F(SSDReaderFileManagerMockFixture, ExceptionWriteWithMock) {
    bool result;
    int index = 0;

    EXPECT_CALL(mock, read(nand_file, index))
        .Times(1)
        .WillRepeatedly(Return(string(value)));

    EXPECT_CALL(mock, write(result_file, value))
        .Times(1)
        .WillOnce(Throw(exception()));

    SSDReader reader{ &mock };
    result = reader.read(nand_file, result_file, index);
    EXPECT_THAT(result, Eq(false));
}


TEST(SSDReaderTest, NormalReadTest) {
    FileManager m;
    bool result;

    int index = 0;
    string nand_file = NAND_NAME_PATH;
    string result_file = RESULT_NAME_PATH;

    SSDReader reader{ &m };
    result = reader.read(nand_file, result_file, index);

    EXPECT_THAT(result, Eq(true));
}
