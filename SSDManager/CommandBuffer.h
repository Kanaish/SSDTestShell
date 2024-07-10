/* Copyright 2024 Code Love you */
#pragma once
#include <string>
class CommandBuffer {
public:
    CommandBuffer() {
        createCommandBuffer();
    }
    bool SetCommandBuffer(const std::string& cmd, int index, const std::string& value);

private:
    bool createCommandBuffer();
    bool isCommandbyIndex(const std::string& cmd, int index, size_t& pos);
    void addCommandBuffer(int index, const std::string& cmd, const std::string& value);
    void modifyCommandBuffer(size_t pos, int index, const std::string& cmd, const std::string& value);

    std::string generateLBAString(int index);
    std::string generateCmdString(int index, std::string cmd);
    std::string generateValueString(int index, std::string cmd, std::string value);

    const std::string CMD_BUF_FILE_NAME = "../resources/buffer.txt";
    const std::string LBA_STRING = "LBA";
};