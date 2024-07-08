/* Copyright 2024 Code Love you */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/FileManager.cpp"

#define TEST_INDEX  (0)
#define TEST_VALUE  (0xAAAAAAAA)

using namespace std;

TEST(FileManagerTest, file_manager_test_init) {
    FileManager fm;
    EXPECT_THAT(fm.init("test.txt"), testing::IsNull());
}

TEST(FileManagerTest, file_manager_test_open) {
    FileManager fm;
    EXPECT_THAT(fm.open("test.txt"), testing::IsNull());
}

TEST(FileManagerTest, file_manager_test_read) {
    FileManager fm;
    fstream * fs = fm.open("test.txt");
    EXPECT_THAT(fm.read(fs, TEST_INDEX), 0);
}

TEST(FileManagerTest, file_manager_test_write) {
    FileManager fm;
    fstream* fs = fm.open("test.txt");
    EXPECT_THAT(fm.write(fs, TEST_INDEX, TEST_VALUE), true);
}

TEST(FileManagerTest, file_manager_test_write_during_read) {
    FileManager fm;
    fstream* fs = fm.open("test.txt");
    EXPECT_THAT(fm.write(fs, TEST_VALUE), true);
}

TEST(FileManagerTest, file_manager_test_close) {
    FileManager fm;
    fstream* fs = fm.open("test.txt");
    EXPECT_THAT(fm.close(fs), true);
}
