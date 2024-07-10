/* Copyright 2024 Code Love you */

#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"

using namespace std;
using namespace testing;

class TestShellMock : public TestShell {
public:
    MOCK_METHOD(int, write, (const string& arg), (override));
    MOCK_METHOD(int, read, (const string& arg), (override));
    MOCK_METHOD(void, exit, (), (override));
    MOCK_METHOD(void, help, (), (override));
    MOCK_METHOD(int, fullWrite, (const string& arg), (override));
    MOCK_METHOD(int, fullRead, (), (override));
    MOCK_METHOD(int, testApp1, (), (override));
    MOCK_METHOD(int, testApp2, (), (override));
};

class TestShellFixture : public Test {
protected:
    TestShell shell;
    NiceMock<TestShellMock> mock;
    string str;

    void expectInvalidArgumentForWrite(const string& command) {
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

TEST_F(TestShellFixture, execute_invalid_command1) {
    expectInvalidArgumentForWrite("writ 3 0xAAAABBBB");
}

TEST_F(TestShellFixture, execute_invalid_command2) {
    expectInvalidArgumentForWrite("writ 3 0xAAAABBBB fff");
}

TEST_F(TestShellFixture, execute_invalid_command3) {
    expectInvalidArgumentForWrite("exit 4");
}

TEST_F(TestShellFixture, execute_write) {
    EXPECT_CALL(mock, write("3 0xAAAABBBB")).Times(1);
    mock.execute("write 3 0xAAAABBBB");
}

TEST_F(TestShellFixture, execute_read) {
    EXPECT_CALL(mock, read("3")).Times(1);
    mock.execute("read 3");
}

TEST_F(TestShellFixture, execute_exit) {
    EXPECT_CALL(mock, exit).Times(1);
    mock.execute("exit");
}

TEST_F(TestShellFixture, execute_help) {
    EXPECT_CALL(mock, help).Times(1);
    mock.execute("help");
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
    EXPECT_EQ(mock.fullWrite(""), -1);
}

TEST_F(TestShellFixture, fullWrite_pass) {
    EXPECT_CALL(mock, write(_)).Times(100)
        .WillRepeatedly(Return(0));

    mock.fullWrite("0x12345678");
}

TEST_F(TestShellFixture, fullRead_pass) {
    EXPECT_CALL(mock, read(_)).Times(100)
        .WillRepeatedly(Return(0));

    mock.fullRead();
}

TEST_F(TestShellFixture, testApp1_pass) {
    EXPECT_CALL(mock, fullWrite("0xAAAABBBB")).Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(mock, fullRead()).Times(1)
        .WillOnce(Return(0));
    EXPECT_EQ(mock.TestShell::testApp1(), 0);
}

TEST_F(TestShellFixture, testApp2_pass) {
    EXPECT_CALL(mock, write(_))
        .Times(36)  
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mock, read(_))
        .Times(6)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(mock.testApp2(), 0);
}