/* Copyright 2024 Code Love you */

#include <stdexcept>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/CommandBuffer.cpp"

/*
typedef struct BufferData {
    char cmd;
    int index;
    std::string write_value;
    int erase_size;
};
*/
TEST(CommandBufferTest, SetCommandBufferTest) {
    CommandBuffer buf;
    BufferData data = { 'W', 1, "0x55555555", 0 };
    buf.updateBuffer(data);
}