/* Copyright 2024 Code Love you */
#include <iostream>
#include <fstream>
#include <sstream>
#include "CommandBuffer.h"

bool CommandBuffer::createCommandBuffer() {
    static bool isCreated = false;
   
    if (isCreated == true) return true;

    std::fstream bufferFile(CMD_BUF_FILE_NAME);
    if (!bufferFile.is_open()) {
        std::ofstream ofs(CMD_BUF_FILE_NAME);
        if (ofs.fail())
        {
            throw std::exception("File is not opened");
            return false;
        }
    }
    isCreated = true;
    return true;
}
bool CommandBuffer::SetCommandBuffer(const std::string& cmd, int index, const std::string& value) {
    size_t pos;

    bool ret = isCommandbyIndex(cmd, index, pos);
    if (ret == true) {
        modifyCommandBuffer(pos, index, cmd, value);
    }
    else {
        addCommandBuffer(index, cmd, value);
    }

    return ret;
}
void CommandBuffer::addCommandBuffer(int index, const std::string& cmd, const std::string& value)
{
    std::fstream bufferFile(CMD_BUF_FILE_NAME, std::ios::in | std::ios::out);
    bufferFile.seekp(0, std::ios::end);
    bufferFile << generateValueString(index, cmd, value);
    bufferFile.close();
}
void CommandBuffer::modifyCommandBuffer(size_t pos, int index, const std::string& cmd, const std::string& value)
{
    std::fstream bufferFile(CMD_BUF_FILE_NAME, std::ios::in | std::ios::out);
    bufferFile.seekp(pos, std::ios::beg);
    bufferFile << generateValueString(index, cmd, value);
    bufferFile.close();
}
bool CommandBuffer::isCommandbyIndex(const std::string& cmd, int index, size_t& pos) {
    bool ret;

    std::fstream bufferFile(CMD_BUF_FILE_NAME, std::ios::in | std::ios::out);

    if (bufferFile.is_open()) {
        bufferFile.seekp(0, std::ios::beg);

        std::stringstream buffer;
        buffer << bufferFile.rdbuf();
        /* Move file pointer to the beginning */
        bufferFile.seekp(0, std::ios::beg);
        /* Find token in nand */
        pos = buffer.str().find(generateCmdString(index, cmd));
        if (pos != std::string::npos) {
            /* If token is found, replace LBA with given value */
            ret = true;
        }
        else {
            ret = false;
        }
    }
    else {
        throw std::invalid_argument("File is not opened");
        return false;
    }
    bufferFile.close();
    return ret;
}
std::string CommandBuffer::generateLBAString(int index)
{
    return std::string(LBA_STRING + std::to_string(index));
}
std::string CommandBuffer::generateCmdString(int index, std::string cmd)
{
    return std::string(generateLBAString(index) + " " + cmd);
}
std::string CommandBuffer::generateValueString(int index, std::string cmd, std::string value)
{
    return std::string(generateCmdString(index, cmd) + " " + value + " ");
}