#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/FileManager.cpp"

using namespace testing;
TEST(FileManagerTest, file_manager_test_00) 
{
	FileManager fm;
	EXPECT_THAT(fm.open("test.txt"), IsNull());
}