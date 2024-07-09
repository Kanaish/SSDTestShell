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

TEST(SSDManagerTest, validOkayTest) {
    // Arrange
    int argc = 4;
    char* argv[] = { "ssd", "W", "2", "0x1298CDEF" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), true);
}

TEST(SSDManagerTest, validFailTest1) {
    // Arrange
    int argc = 1;
    char* argv[] = { "ssd" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}

TEST(SSDManagerTest, validFailTest2) {
    // Arrange
    int argc = 4;
    char* argv[] = { "ssd", "Write", "2", "0x1298CDEF" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}

TEST(SSDManagerTest, validFailTest3) {
    // Arrange
    int argc = 4;
    char* argv[] = { "ssd", "W", "ABC", "0x1298CDEF" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}

TEST(SSDManagerTest, validFailTest4) {
    // Arrange
    int argc = 4;
    char* argv[] = { "ssd", "W", "100", "0x1298CDEF" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}

TEST(SSDManagerTest, validFailTest5) {
    // Arrange
    int argc = 3;
    char* argv[] = { "ssd", "W", "2" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}

TEST(SSDManagerTest, validFailTest6) {
    // Arrange
    int argc = 4;
    char* argv[] = { "ssd", "W", "2", "0x1234ABCD1234ABCD"};
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}

TEST(SSDManagerTest, validFailTest7) {
    // Arrange
    int argc = 4;
    char* argv[] = { "ssd", "W", "2", "1234ABCD1234ABCD" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}

TEST(SSDManagerTest, validFailTes8) {
    // Arrange
    int argc = 4;
    char* argv[] = { "ssd", "W", "2", "0xABCDEFGH" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}

TEST(SSDManagerTest, validFailTes9) {
    // Arrange
    int argc = 4;
    char* argv[] = { "ssd", "R", "2", "0xABCDEFGH" };
    SSDManager ssd(argc, argv);

    // Act, Assert
    EXPECT_EQ(ssd.isValidInput(), false);
}
