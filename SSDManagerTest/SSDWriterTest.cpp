/* Copyright 2024 Code Love you */

#include <iostream>
#include <fstream>
#include <cstdio>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/SSDWriter.cpp"
#include "../SSDManager/FileManagerInterface.h"

using namespace std;
using namespace testing;

class FileManagerWriterMock :public FileManagerInterface {
 public:
    MOCK_METHOD(string, read, (string name), (override));
    MOCK_METHOD(string, read, (string name, int index), (override));
    MOCK_METHOD(bool, write, (string name, int index,
                                           string value), (override));
    MOCK_METHOD(bool, write, (string name, string value), (override));
};


class SSDWriteTestFixture :public Test {
 public:
    FileManagerWriterMock fm;
    SSDWriter ssd_writer{ &fm };
    string nand_file = "nand.txt";
    int index = 1;
    string write_value = "0x00000000";
};

// Write Checke behavior -> call once ,true return
TEST_F(SSDWriteTestFixture, Write_behavior_call_fm_write_functon) {
    EXPECT_CALL(fm, write(nand_file, index, write_value))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_THAT(ssd_writer.write(nand_file, index, write_value), IsTrue());
}
// ssd_writer behavior EXCEPTION Case False Return
TEST_F(SSDWriteTestFixture, Write_behavior_Exception_return_false_check) {
    EXPECT_CALL(fm, write(nand_file, index, write_value)).Times(1)
        .WillOnce(Throw(std::exception()));
    EXPECT_THAT(ssd_writer.write(nand_file, index, write_value), IsFalse());
}

