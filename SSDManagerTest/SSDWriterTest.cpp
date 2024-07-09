//    "Copyright [2024] <YD>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/SSDWriter.cpp"
using namespace std;
using namespace testing;
// create SSDWriter Class  get filestream   nullptr Check
TEST(SSDWriter, init_fileptrnull) {
    SSDWriter ssd_writer;
    EXPECT_THAT(ssd_writer.getNandFileStream(), NotNull());
}
// ssd_writer behavior EXCEPTION Check
TEST(SSDWriter, check_wirterfunction_no_exception) {
    SSDWriter ssd_writer;
    int index = 9;
    int value = 10;
    EXPECT_NO_THROW(ssd_writer.writer(index, value));
}
