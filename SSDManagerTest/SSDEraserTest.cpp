/* Copyright 2024 Code Love you */
#include <iostream>
#include <fstream>
#include <cstdio>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/SSDEraser.cpp"
#include "../SSDManager/FileManagerInterface.h"

using namespace std;
using namespace testing;

class FileManagerEraserMock :public FileManagerInterface {
public:
    MOCK_METHOD(string, read, (string name), (override));
    MOCK_METHOD(string, read, (string name, int index), (override));
    MOCK_METHOD(bool, write, (string name, int index, string value), (override));
    MOCK_METHOD(bool, write, (string name, string value), (override));
};


class FileManagerEraserFixture :public Test {
public:
    FileManager m;
    SSDEraser ssd_real_eraser{ &m };
    FileManagerEraserMock fm;
    SSDEraser ssd_eraser{ &fm };
    const string NAND_FILE = "test_nand.txt";
    const int TEST_START_INDEX = 10;
    const int TEST_ERASE_SIZE = 10;
    const string TEST_INIT_VALUE = "0x00000000";

};
//// ssd_eraser Normal behavior Test -> Erase test_nand.txt
TEST_F(FileManagerEraserFixture, easer_normal_function_Test) {
    bool result = ssd_real_eraser.erase(NAND_FILE, TEST_START_INDEX, TEST_ERASE_SIZE);
    EXPECT_THAT(result, testing::Eq(true));
}

//// ssd_eraser behavior Test  Case False Return
TEST_F(FileManagerEraserFixture, erase_behavior_call_fm_write_functon) {

    EXPECT_CALL(fm, write(NAND_FILE, _, TEST_INIT_VALUE))
        .Times(TEST_ERASE_SIZE)
        .WillRepeatedly(Return(true));

    EXPECT_THAT(ssd_eraser.erase(NAND_FILE, TEST_START_INDEX, TEST_ERASE_SIZE), IsTrue());
}


// ssd_eraser behavior EXCEPTION Case False Return
TEST_F(FileManagerEraserFixture, Write_behavior_Exception_return_false_check) {

    EXPECT_CALL(fm, write(NAND_FILE, TEST_START_INDEX, TEST_INIT_VALUE))
        .Times(1)
        .WillOnce(Throw(std::exception()));

    EXPECT_THAT(ssd_eraser.erase(NAND_FILE, TEST_START_INDEX, TEST_ERASE_SIZE), IsFalse());
}



