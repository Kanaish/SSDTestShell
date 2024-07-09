#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"

using namespace std;

TEST(ShellTest, execute_test_invalid_command) {
	string str{ "writ 3 0xAAAABBBB" };
	TestShell shell;
	EXPECT_THROW(shell.execute(str), runtime_error);
}

TEST(ShellTest, execute_test_invalid_argument) {
	string str{ "read 3 0xAAAABBB0CC" };
	TestShell shell;
	EXPECT_THROW(shell.execute(str), runtime_error);
}

TEST(ShellTest, execute_test_invalid_argument2) {
	string str{ "read 100 0xAAAABBB0" };
	TestShell shell;
	EXPECT_THROW(shell.execute(str), runtime_error);
}

