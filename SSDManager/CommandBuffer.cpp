/* Copyright 2024 Code Love you */
#include <iostream>
#include <fstream>
#include <sstream>
#include "CommandBuffer.h"

CommandBuffer::CommandBuffer() {
	createBufferFile();
}

bool CommandBuffer::updateBuffer(BufferData data) {
    if (readBufferFile() == false) {
        return false;
    }

    return true;
}

bool CommandBuffer::isFullBuffer() {
    return true;
}

std::vector<BufferData> CommandBuffer::flushBuffer() {
    std::vector<BufferData> data;
    return data;
}

std::string CommandBuffer::findMatchedWrite(int index) {
    return "";
}

bool CommandBuffer::createBufferFile() {
    std::fstream bufferFile(BUFFER_FILE_NAME);
    if (!bufferFile) {
        std::ofstream ofs(BUFFER_FILE_NAME);
        if (!ofs)
        {
            return false;
        }
    }
    return true;
}

bool CommandBuffer::readBufferFile() {
    std::fstream bufferFile(BUFFER_FILE_NAME);
    if (!bufferFile) {
        return false;
    }

    /* read nand and store to the buffer */
    std::stringstream buffer;
    std::string cmd;
    buffer << bufferFile.rdbuf();
    
    std::string token;
    BufferData buf_data;

    // 구분자로 쉼표(,)를 사용하여 문자열 추출
    while (std::getline(buffer, cmd, DELIMETER_STRING)) {
        buf_data = {};

        if (cmd[0] == 'W') {
            std::stringstream cmd_stream;
            cmd_stream << cmd;

            std::getline(cmd_stream, token, SPACE_STRING);
            buf_data.cmd = 'W';

            std::getline(cmd_stream, token, SPACE_STRING);
            buf_data.index = stoi(token);

            std::getline(cmd_stream, token, SPACE_STRING);
            buf_data.write_value = token;

            data.push_back(buf_data);
        }
        else if (cmd[0] == 'E') {
            std::stringstream cmd_stream;
            cmd_stream << cmd;

            std::getline(cmd_stream, token, SPACE_STRING);
            buf_data.cmd = 'E';

            std::getline(cmd_stream, token, SPACE_STRING);
            buf_data.index = stoi(token);

            std::getline(cmd_stream, token, SPACE_STRING);
            buf_data.erase_size = stoi(token);

            data.push_back(buf_data);
        }

    }
    return true;
}

bool CommandBuffer::writeBufferFile() {
    return true;
}

bool CommandBuffer::flushBufferFile() {
    return true;
}