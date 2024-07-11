/* Copyright 2024 Code Love you */

#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"
#include "../TestShell/FileManager.cpp"

using namespace std;
using namespace testing;

class MockFileManager : public FileManagerInterface {
 public:
    MOCK_METHOD(string, read, (string name), (override));
    MOCK_METHOD(string, read, (string name, int index), (override));
    MOCK_METHOD(bool, write, (string name, int index, string value), (override));
    MOCK_METHOD(bool, write, (string name, string value), (override));
};

class TestShellWithMockFileManager : public TestShell {
 public:
    explicit TestShellWithMockFileManager(FileManagerInterface* fileManager)
        : TestShell(fileManager) {}

    MOCK_METHOD(int, write, (const string& arg), (override));
    MOCK_METHOD(int, read, (const string& arg, bool isPrint), (override));
    MOCK_METHOD(int, exit, (), (override));
    MOCK_METHOD(int, help, (), (override));
};

class TestShellFixture : public Test {
 protected:
    NiceMock<MockFileManager> mockFileManager;
    NiceMock<TestShellWithMockFileManager> shellWithMock;
    FileManager file_manager;
    TestShell shell{ &file_manager };

    TestShellFixture()
        : shellWithMock(&mockFileManager), shell(&file_manager) {}

    void expectInvalidArgumentForFullWrite(const string& command) {
        try {
            shellWithMock.fullWrite(command);
            FAIL() << "Expected invalid_argument";
        }
        catch (const invalid_argument& e) {
            EXPECT_EQ(string(e.what()), "INVALID COMMAND");
        }
        catch (...) {
            FAIL() << "Expected invalid_argument";
        }
    }

    void expectInvalidArgumentForWrite(const string & command) {
        try {
            shell.write(command);
            FAIL() << "Expected invalid_argument";
        }
        catch (const invalid_argument& e) {
            EXPECT_EQ(string(e.what()), "INVALID COMMAND");
        }
        catch (...) {
            FAIL() << "Expected invalid_argument";
        }
    }

    void expectInvalidArgumentForRead(const string& command) {
        try {
            shell.read(command);
            FAIL() << "Expected invalid_argument";
        }
        catch (const invalid_argument& e) {
            EXPECT_EQ(string(e.what()), "INVALID COMMAND");
        }
        catch (...) {
            FAIL() << "Expected invalid_argument";
        }
    }
};

TEST_F(TestShellFixture, execute_invalid_command) {
    expectInvalidArgumentForWrite("writ 3 0xAAAABBBB");
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
    expectInvalidArgumentForWrite("");
}

TEST_F(TestShellFixture, write_invalid_argument2) {
    expectInvalidArgumentForWrite("write 3 0xAAAABBBB00");
}

TEST_F(TestShellFixture, read_invalid_argument1) {
    expectInvalidArgumentForRead("");
}

TEST_F(TestShellFixture, read_invalid_argument2) {
    expectInvalidArgumentForRead("read 100");
}

TEST_F(TestShellFixture, fullWrite_fail) {
    expectInvalidArgumentForFullWrite("");
}

TEST_F(TestShellFixture, fullWrite_pass) {
    EXPECT_CALL(shellWithMock, write(_))
        .Times(100)
        .WillRepeatedly(Return(0));
    EXPECT_EQ(shellWithMock.fullWrite("0x12345678"), 0);
}

TEST_F(TestShellFixture, fullRead_pass) {
    EXPECT_CALL(shellWithMock, read(_, _))
        .Times(100)
        .WillRepeatedly(Return(0));
    EXPECT_EQ(shellWithMock.fullRead(), 0);
}

TEST_F(TestShellFixture, testApp1_pass) {
    EXPECT_CALL(shellWithMock, write(_))
        .Times(100)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(shellWithMock, read(_, _))
        .Times(100)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockFileManager, read(_))
        .Times(100)
        .WillRepeatedly(Return("0xAAAABBBB"));
    EXPECT_EQ(shellWithMock.testApp1(), 0);
}

TEST_F(TestShellFixture, testApp2_pass) {
    EXPECT_CALL(shellWithMock, write(_))
        .Times(186)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockFileManager, read(_)).
        Times(6)
        .WillRepeatedly(Return("0x12345678"));
    EXPECT_EQ(shellWithMock.testApp2(), 0);
}
