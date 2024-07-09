/* Copyright 2024 Code Love you */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/SSDManager.cpp"

using namespace std;

TEST(SSDManagerTest, constructorTest) {
    // Arrange
    int argc = 4;
    char* argv[] = {"ssd", "W", "2", "0x1298CDEF"};
    vector<string> expected = { "ssd", "W", "2", "0x1298CDEF" };

    // Act
    SSDManager ssd(argc, argv);

    // Assert
    EXPECT_EQ(ssd.getParsedCommand(), expected);
}
