/* Copyright 2024 Code Love you */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/FileManager.cpp"
#include "../SSDManager/FileManagerInterface.h"

#define TEST_INDEX     (0)
#define TEST_VALUE     "0xAAAAAAAA"

#define TEST_RESULT    "test_result.txt"
#define TEST_NAND      "test_nand.txt"
#define TEST_NAND_REF  "test_nand_ref.txt"

using namespace std;
using namespace testing;

TEST(FileManagerTest, file_manager_test_read) {
    FileManager fm;
    EXPECT_THAT(fm.read(TEST_RESULT, TEST_INDEX), "");
}

TEST(FileManagerTest, file_manager_test_write_different_index) {
    FileManager fm;
    stringstream testBuf, testRef;
    string textBuf, textRef;

    fstream testFile(TEST_NAND, std::ios::in | std::ios::out | std::ios::trunc);
    for (int i = 0; i < 100; i++)
    {
        fm.write(TEST_NAND, i, "0x" + to_string(10000000 + i));
    }
    
    fstream refFile(TEST_NAND_REF, std::ios::in | std::ios::out | std::ios::beg);

    testBuf << testFile.rdbuf();
    testRef << refFile.rdbuf();

    textBuf = testBuf.str();
    textRef = testRef.str();

    EXPECT_EQ(textBuf, textRef);
}

TEST(FileManagerTest, file_manager_test_write_during_read) {
    FileManager fm;
    EXPECT_THAT(fm.write(TEST_RESULT, TEST_VALUE), true);
}
