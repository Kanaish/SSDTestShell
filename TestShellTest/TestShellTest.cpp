/* Copyright 2024 Code Love you */

#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"
#include "../SSDManager/FileManager.cpp"
#include "../SSDManager/LogManager.cpp"
#include "../SSDAPILibrary/SSDAPILibrary.cpp"

using namespace std;
using namespace testing;

class TestShellMock : public TestShell {
 public:
    explicit TestShellMock(FileManagerInterface* fileManager)
        : TestShell(fileManager) {}

    MOCK_METHOD(int, write, (const string& arg), (override));
    MOCK_METHOD(int, read, (const string& arg, bool isPrint), (override));
    MOCK_METHOD(int, exit, (), (override));
    MOCK_METHOD(int, help, (), (override));
};

class TestShellFixture : public Test {
    void SetUp() override {
        _chdir("../x64/Debug");
    }
 protected:
    NiceMock<TestShellMock> shellWithMock;
    FileManager file_manager;
    TestShell shell{ &file_manager };

    TestShellFixture()
        : shellWithMock(&file_manager), shell(&file_manager) {}
};

TEST_F(TestShellFixture, execute_invalid_command) {
    try {
        shell.execute("writ");
        FAIL() << "Expected invalid_argument";
    }
    catch (const invalid_argument& e) {
        EXPECT_EQ(string(e.what()), "INVALID COMMAND");
    }
    catch (...) {
        FAIL() << "Expected invalid_argument";
    }
}

TEST_F(TestShellFixture, execute_write) {
    EXPECT_CALL(shellWithMock, write("3 0xAAAABBBB")).Times(1)
        .WillOnce(Return(0));
    shellWithMock.execute("write 3 0xAAAABBBB");
}

TEST_F(TestShellFixture, execute_read) {
    EXPECT_CALL(shellWithMock, read("3", true))
        .Times(1)
        .WillOnce(Return(0));
    shellWithMock.execute("read 3");
}

TEST_F(TestShellFixture, execute_exit) {
    EXPECT_CALL(shellWithMock, exit()).Times(1);
    shellWithMock.execute("exit");
}

TEST_F(TestShellFixture, execute_help) {
    EXPECT_CALL(shellWithMock, help()).Times(1);
    shellWithMock.execute("help");
}

TEST_F(TestShellFixture, write_invalid_argument1) {
    EXPECT_EQ(shell.write(""), TestShell::INVALID_COMMAND);
}

TEST_F(TestShellFixture, write_invalid_argument2) {
    EXPECT_EQ(shell.write("0xAAAABBBB00"), TestShell::INVALID_COMMAND);
}

TEST_F(TestShellFixture, read_invalid_argument1) {
    EXPECT_EQ(shell.read(""), TestShell::INVALID_COMMAND);
}

TEST_F(TestShellFixture, read_invalid_argument2) {
    EXPECT_EQ(shell.read("read 100"), TestShell::INVALID_COMMAND);
}

TEST_F(TestShellFixture, fullWrite_fail) {
    EXPECT_EQ(shell.fullWrite(""), TestShell::INVALID_COMMAND);
}

TEST_F(TestShellFixture, fullWrite_pass) {
    EXPECT_EQ(shell.fullWrite("0x12345678"), 0);
}

TEST_F(TestShellFixture, fullRead_pass) {
    EXPECT_EQ(shell.fullRead(), 0);
}

TEST_F(TestShellFixture, testApp1_pass) {
    EXPECT_EQ(shell.testApp1(), 0);
}

TEST_F(TestShellFixture, testApp2_pass) {
    EXPECT_EQ(shell.testApp2(), 0);
}
