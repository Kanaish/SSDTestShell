#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"

using namespace std;

TEST(ShellTest, execute_test_invalid_command) {
	TestShell shell;
	std::string str{ "writ 3 0xAAAABBBB" };
	EXPECT_THROW(shell.execute(str), runtime_error);
}

TEST(ShellTest, execute_test_invalid_argument1) {
	TestShell shell;
	std::string str{ "read 3 0xAAAABBBB00" };
	EXPECT_THROW(shell.execute(str), runtime_error);
}

TEST(ShellTest, execute_test_invalid_argument2) {
	TestShell shell;
	std::string str{ "read 100 0xAAAABBBB" };
	EXPECT_THROW(shell.execute(str), runtime_error);
}