/* Copyright 2024 Code Love you */

#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"

using namespace std;

class TestShellMock : public TestShell {
 public:
  MOCK_METHOD(bool, write, (const std::string& arg), (override));
  MOCK_METHOD(bool, read, (const std::string& arg), (override));
  MOCK_METHOD(void, exit, (), (override));
  MOCK_METHOD(void, help, (), (override));
  MOCK_METHOD(bool, fullWrite, (const std::string& arg), (override));
  MOCK_METHOD(bool, fullRead, (), (override));
};

class TestShellFixture : public testing::Test {
 protected:
  TestShell shell;
  TestShellMock mock;
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
  str = "write 3 0xAAAABBBB";
  EXPECT_CALL(mock, write(str)).Times(1);
  shell.execute(str);
}

TEST_F(TestShellFixture, execute_read) {
  str = "read 3";
  EXPECT_CALL(mock, read(str)).Times(1);
  shell.execute(str);
}

TEST_F(TestShellFixture, execute_exit) {
  EXPECT_CALL(mock, exit).Times(1);
  shell.execute("exit");
}

TEST_F(TestShellFixture, execute_help) {
  EXPECT_CALL(mock, help).Times(1);
  shell.execute("help");
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

TEST_F(TestShellFixture, fullWrite_invalid_argument1) {
  shell.fullWrite("");
}

TEST_F(TestShellFixture, fullWrite_pass) {
  str = "write 3 0xAAAABBBB";
  EXPECT_CALL(mock, write(str)).Times(100);
  shell.fullWrite(str);
}

TEST_F(TestShellFixture, fullRead_pass) {
  EXPECT_CALL(mock, read("read")).Times(100);
  shell.fullRead();
}
