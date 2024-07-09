/* Copyright 2024 Code Love you */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/FileManager.cpp"
#include "../SSDManager/FileManagerInterface.h"
#include <string>

#define TEST_INDEX  (0)
#define TEST_VALUE  ("0xAAAAAAAA")

#define TEST_RESULT ("result.txt")
#define TEST_NAND   ("nand.txt")

using namespace std;
using namespace testing;

class FileManagerMock : public FileManager {
public:
    MOCK_METHOD(bool, write, (string, int, string), ());
};

TEST(FileManagerTest, file_manager_test_init) {
    FileManager fm;
    EXPECT_THAT(fm.init(TEST_RESULT), true);
}

TEST(FileManagerTest, file_manager_test_open) {
    FileManager fm;
    EXPECT_THAT(fm.open(TEST_RESULT), true);
}

TEST(FileManagerTest, file_manager_test_close) {
    FileManager fm;
    EXPECT_THAT(fm.close(TEST_RESULT), true);

}
TEST(FileManagerTest, file_manager_test_read) {
    FileManager fm;
    EXPECT_THAT(fm.read(TEST_RESULT, TEST_INDEX), "");
}

TEST(FileManagerTest, file_manager_test_write) {
    FileManager fm;
    FileManagerMock fmMock;
    EXPECT_CALL(fmMock, write(TEST_NAND, TEST_INDEX, TEST_VALUE))
        .WillOnce(Return(true));
    EXPECT_EQ(fmMock.write(TEST_NAND, TEST_INDEX, TEST_VALUE), true);
}

TEST(FileManagerTest, file_manager_test_write_during_read) {
    FileManager fm;
    EXPECT_THAT(fm.write(TEST_RESULT, TEST_VALUE), true);
}
