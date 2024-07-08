#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../SSDManager/SSDWriter.cpp"
#include "../SSDManager/iFileManager.h"


class FileManagerMock :public FileManager{
public:
	MOCK_METHOD(bool, write, (fstream* fs, int index, unsigned int  value), (override));
	MOCK_METHOD(bool, init, (), (override));
	MOCK_METHOD(bool, close, (fstream* fs), (override));
};



//생성자 init 호출 
TEST(SSDWriter, Create_Class) {

	FileManagerMock fm;
	EXPECT_CALL(fm, init()).Times(1);
	SSDWriter ssd_writer(&fm);


}



//생성자 init 호출 
TEST(SSDWriter, Create_Class) {

	FileManagerMock fm;
	EXPECT_CALL(fm, init()).Times(1);
	SSDWriter ssd_writer(&fm);


}