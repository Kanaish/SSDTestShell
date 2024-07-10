/* Copyright 2024 Code Love you */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/FileManager.cpp"
#include "../SSDManager/FileManagerInterface.h"

#define TEST_RESULT          "test_result.txt"
#define TEST_NAND            "test_nand.txt"
#define TEST_NAND_DIFF       "test_nand_diff.txt"
#define TEST_NAND_REF        "test_nand_ref.txt"
#define TEST_NAND_DIFF_REF   "test_nand_diff_ref.txt"

#define TEST_NAND_DIFF_MOD                  (25)
#define TEST_NAND_MOD                       (100)
#define TEST_NAND_MOD_FOR_EMPTY_READ        (50)

using namespace std;
using namespace testing;

class FileManagerMock : public FileManagerInterface
{
public:
    MOCK_METHOD(bool, write , (string, int, string), ());
    MOCK_METHOD(bool, write, (string, string), ());
    MOCK_METHOD(bool, read, (string, string), ());
};
class FileManagerTestFixture : public Test {
public:
    FileManager fm;
    stringstream testBuf, testRef;
    string textBuf = "";
    string textRef = "";
    stringstream resultTestBuf;
    string resultTextBuf = "";
    void testWrite(string name, int mod)
    {
        for (int i = 0; i < 100; i++) {
            fm.write(name, i % mod, "0x" + to_string(10000000 + i));
        }
    }
    fstream testFile{ TEST_NAND, std::ios::in | std::ios::out | std::ios::trunc };
    fstream refFile{ TEST_NAND_REF, std::ios::in | std::ios::out | std::ios::beg };
    fstream testDiffFile{ TEST_NAND_DIFF, std::ios::in | std::ios::out | std::ios::trunc };
    fstream refDiffFile{ TEST_NAND_DIFF_REF, std::ios::in | std::ios::out | std::ios::beg };
    fstream testResultFile{ TEST_RESULT, std::ios::in | std::ios::out | std::ios::trunc };
};

TEST_F(FileManagerTestFixture, file_manager_test_read) {
    testWrite(TEST_NAND, TEST_NAND_MOD);

    EXPECT_THAT(fm.read(TEST_NAND, 0), "0x10000000");
    EXPECT_THAT(fm.read(TEST_NAND, 99), "0x10000099");
}

TEST_F(FileManagerTestFixture, file_manager_test_write_different_index) {
    testWrite(TEST_NAND, TEST_NAND_MOD);
    
    testBuf << testFile.rdbuf();
    testRef << refFile.rdbuf();

    textBuf = testBuf.str();
    textRef = testRef.str();

    EXPECT_EQ(textBuf, textRef);
}

TEST_F(FileManagerTestFixture, file_manager_test_write_same_index) {
    testWrite(TEST_NAND_DIFF, TEST_NAND_DIFF_MOD);

    testBuf << testDiffFile.rdbuf();
    testRef << refDiffFile.rdbuf();

    textBuf = testBuf.str();
    textRef = testRef.str();

    EXPECT_EQ(textBuf, textRef);
}

TEST_F(FileManagerTestFixture, file_manager_test_write_during_read) {
    testWrite(TEST_NAND, TEST_NAND_MOD);
    string resultTextRef = fm.read(TEST_NAND, 5);
    fm.write(TEST_RESULT, resultTextRef);

    resultTestBuf << testResultFile.rdbuf();
    resultTextBuf = resultTestBuf.str();

    EXPECT_EQ(resultTextBuf, resultTextRef);
}
