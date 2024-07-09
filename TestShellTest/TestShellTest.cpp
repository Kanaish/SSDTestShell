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

TEST(ShellTest, execute_invalid_command) {
  TestShell shell;
  std::string str{ "writ 3 0xAAAABBBB" };
  try {
    shell.write(str);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "INVALID COMMAND");
  }
  catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(ShellTest, execute_write) {
  TestShell shell;
  TestShellMock mock;
  std::string str{ "write 3 0xAAAABBBB" };
  EXPECT_CALL(mock, write(str)).Times(1);
  shell.execute(str);
}


TEST(ShellTest, execute_read) {
  TestShell shell;
  TestShellMock mock;
  std::string str{ "read 3" };
  EXPECT_CALL(mock, read(str)).Times(1);
  shell.execute(str);
}


TEST(ShellTest, execute_exit) {
  TestShell shell;
  TestShellMock mock;
  std::string str{ "exit" };
  EXPECT_CALL(mock, exit).Times(1);
  shell.execute(str);
}

TEST(ShellTest, execute_help) {
  TestShell shell;
  TestShellMock mock;
  std::string str{ "help" };
  EXPECT_CALL(mock, help).Times(1);
  shell.execute(str);
}

TEST(ShellTest, write_invalid_argument1) {
  TestShell shell;
  std::string str{ "" };
  try {
    shell.write(str);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "INVALID COMMAND");
  }
  catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(ShellTest, write_invalid_argument2) {
  TestShell shell;
  std::string str{ "write 3 0xAAAABBBB00" };
  try {
    shell.write(str);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "INVALID COMMAND");
  }
  catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(ShellTest, read_invalid_argument1) {
  TestShell shell;
  std::string str{ "" };
  try {
    shell.write(str);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "INVALID COMMAND");
  }
  catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(ShellTest, read_invalid_argument2) {
  TestShell shell;
  std::string str{ "read 100" };
  try {
    shell.write(str);
    FAIL() << "Expected std::invalid_argument";
  }
  catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "INVALID COMMAND");
  }
  catch (...) {
    FAIL() << "Expected std::invalid_argument";
  }
}

TEST(ShellTest, fullWrite_invalid_argument1) {
  TestShell shell;
  std::string str{ "" };
  shell.fullWrite(str);
}

TEST(ShellTest, fullWrite_pass) {
  TestShell shell;
  TestShellMock mock;
  std::string str{ "write 3 0xAAAABBBB" };
  EXPECT_CALL(mock, write(str)).Times(100);
  shell.fullWrite(str);
}

TEST(ShellTest, fullRead_pass) {
  TestShell shell;
  TestShellMock mock;
  std::string str{ "read" };
  EXPECT_CALL(mock, read(str)).Times(100);
  shell.fullRead();
}