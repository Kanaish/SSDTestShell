/* Copyright 2024 Code Love you */

#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"

using namespace std;

class TestShellMock : public TestShell {
 public:
  MOCK_METHOD(bool, write, (string cmd), (override));
  MOCK_METHOD(bool, read, (string cmd), (override));
};

TEST(ShellTest, execute_test_invalid_command) {
  TestShell shell;
  std::string str{ "writ 3 0xAAAABBBB" };
  EXPECT_THROW(shell.execute(str), runtime_error);
}

TEST(ShellTest, execute_test_invalid_argument1) {
  TestShell shell;
  std::string str{ "write 3 0xAAAABBBB00" };
  EXPECT_THROW(shell.execute(str), runtime_error);
}

TEST(ShellTest, execute_test_invalid_argument2) {
  TestShell shell;
  std::string str{ "read 100" };
  EXPECT_THROW(shell.execute(str), runtime_error);
}

TEST(ShellTest, execute_test_pass) {
  TestShell shell;
  TestShellMock mock;
  std::string str{ "write 3 0xAAAABBBB" };
  EXPECT_CALL(mock, write(str)).Times(1);
  shell.execute(str);
}