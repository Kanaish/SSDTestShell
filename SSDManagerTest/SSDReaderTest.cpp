/* Copyright 2024 Code Love you */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../SSDManager/SSDReader.cpp"
#include <stdexcept>

using namespace testing;

/*
    std::fstream* open(std::string);
    std::fstream* init(std::string name);
    unsigned int read(std::fstream* fs, int index);
    bool write(std::fstream* fs, int index, unsigned int value);
    bool write(std::fstream* fs, unsigned int value);
    bool close(std::fstream* fs);
*/

class FileManagerMock : public FileManager {
 public:
    MOCK_METHOD(std::fstream*, init, (std::string), (override));
    MOCK_METHOD(std::fstream*, open, (std::string), (override));

    MOCK_METHOD(unsigned int, read, (std::fstream*, int), (override));

    MOCK_METHOD(bool, write, (std::fstream*, int, unsigned int), (override));
    MOCK_METHOD(bool, write, (std::fstream*, unsigned int), (override));

    MOCK_METHOD(bool, close, (std::fstream*), (override));
};

TEST(SSDReaderTest, NormalReadTest) {
    testing::NiceMock<FileManagerMock> mock;
    unsigned int result = 0x12345678;
    int index = 0;
    std::fstream* f_ssd = (std::fstream*) 0x1234;
    std::fstream* f_result = (std::fstream*) 0x5678;

    EXPECT_CALL(mock, init(RESULT_NAME_PATH))
        .Times(1)  // behavior Verification
        .WillRepeatedly(Return(f_result));  // stub Verification
    EXPECT_CALL(mock, open(RESULT_NAME_PATH))
        .Times(1)  //  behavior Verification
        .WillRepeatedly(Return(f_result));  // stub Verification
    EXPECT_CALL(mock, open(NAND_NAME_PATH))
        .Times(1)  // behavior Verification
        .WillRepeatedly(Return(f_ssd));  // stub Verification

    EXPECT_CALL(mock, read(f_ssd, index))
        .Times(1)  // behavior Verification
        .WillRepeatedly(Return(result));  // stub Verification

    EXPECT_CALL(mock, write(f_result, result))
        .Times(1)  // behavior Verification
        .WillRepeatedly(Return(true));  // stub Verification

    SSDReader reader(&mock);
    reader.read(index);
}






