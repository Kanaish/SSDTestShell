/* Copyright 2024 Code Love you */

#include <stdexcept>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDManager/CommandBuffer.cpp"

TEST(CommandBufferTest, SetCommandBufferTest) {
    CommandBuffer buf;
    bool result;
    int index = 0;
    std::string value = "0x22222222";
    result = buf.SetCommandBuffer("W", index, value);

    index = 1;
    value = "0x12345678";
    result = buf.SetCommandBuffer("W", index, value);

    index = 1;
    value = "0x00000000";
    result = buf.SetCommandBuffer("R", index, value);

    index = 1;
    value = "0x00000000";
    result = buf.SetCommandBuffer("E", index, value);
}

