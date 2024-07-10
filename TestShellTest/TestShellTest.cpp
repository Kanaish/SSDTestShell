/* Copyright 2024 Code Love you */

#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"

using namespace std;

class TestShellMock : public TestShell {
public:
    MOCK_METHOD(int, write, (const std::string& arg), (override));
    MOCK_METHOD(int, read, (const std::string& arg), (override));
    MOCK_METHOD(void, exit, (), (override));
    MOCK_METHOD(void, help, (), (override));
    MOCK_METHOD(int, fullWrite, (const std::string& arg), (override));
    MOCK_METHOD(int, fullRead, (), (override));
};

class TestShellFixture : public testing::Test {
protected:
    TestShell shell;
    TestShellMock mock;
    string str;

    void expectInvalidArgumentForWrite(const string& command) {
        try {
            shell.write(command);
            FAIL() << "Expected std::invalid_argument";
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
            FAIL() << "Expected std::invalid_argument";
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
