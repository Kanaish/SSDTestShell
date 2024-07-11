/* Copyright 2024 Code Love you */
#include <iostream>
#include <fstream>
#include <sstream>
#include "CommandBuffer.h"

CommandBuffer::CommandBuffer() {
	createBufferFile();
}

bool CommandBuffer::updateBuffer(BufferData new_data) {
    if (readBufferFile() == false) {
        return false;
    }

    if (new_data.cmd == 'W') {
        ignoreDupWrite(new_data); // Opt1
    }

    return true;
}

void CommandBuffer::ignoreDupWrite(BufferData& new_data)
{
    for (int i = data.size() - 1; i >= 0; i--) {
        if (data[i].cmd == 'W' && data[i].index == new_data.index) {
            data.erase(data.begin() + i);
            break;
        }
    }
    data.push_back(new_data);
}

bool CommandBuffer::isFullBuffer() {
    if (data.size() >= BUFFER_MAX) {
        return true;
    }
    return false;
}

std::vector<BufferData> CommandBuffer::flushBuffer() {
    flushBufferFile();
    return data;
}

std::string CommandBuffer::findMatchedWrite(int index) {
    for (int i = data.size() - 1; i >= 0; i--) {
        if (data[i].index == index && data[i].cmd == 'W') {
            return data[i].write_value;
        }
    }
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
    std::fstream bufferFile(BUFFER_FILE_NAME, std::ios::in);
    if (!bufferFile) {
        return false;
    }

    /* read nand and store to the buffer */
    std::stringstream buffer;
    std::string cmd;
    buffer << bufferFile.rdbuf();
    
    std::string token;
    BufferData buf_data;

    // �����ڷ� ��ǥ(,)�� ����Ͽ� ���ڿ� ����
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
    bufferFile.close();
    return true;
}

bool CommandBuffer::writeBufferFile() {
    std::ofstream bufferFile(BUFFER_FILE_NAME, std::ios::out | std::ios::trunc);
    if (!bufferFile.is_open()) {
        return false;
    }

    std::string cmd_str = "";
    std::string space_str(1, SPACE_STRING);
    std::string delimeter_str(1, DELIMETER_STRING);

    bufferFile.seekp(0, std::ios::end);
    for (auto& cmdData: data) {
        if (cmdData.cmd == 'W') {
            cmd_str = "W" + space_str + std::to_string(cmdData.index) + space_str + cmdData.write_value + delimeter_str;
            bufferFile << cmd_str;
        }
        else if (cmdData.cmd == 'E') {
            cmd_str = "E" + space_str + std::to_string(cmdData.index) + space_str + std::to_string(cmdData.erase_size) + delimeter_str;
            bufferFile << cmd_str;
        }
    }

    bufferFile.close();
    return true;
}

bool CommandBuffer::flushBufferFile() {
    std::ofstream bufferFile(BUFFER_FILE_NAME, std::ios::out | std::ios::trunc);
    if (!bufferFile.is_open()) {
        return false;
    }

    bufferFile.close();
    return true;
}