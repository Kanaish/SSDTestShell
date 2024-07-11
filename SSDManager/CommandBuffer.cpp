/* Copyright 2024 Code Love you */
#include <iostream>
#include <fstream>
#include <sstream>
#include "CommandBuffer.h"
#include "LogManager.h"

CommandBuffer::CommandBuffer() {
    createBufferFile();
    readBufferFile();
}

bool CommandBuffer::updateBuffer(BufferData new_data) {
    if (data.empty()) {
        LOG("Buffer is clean. No need to optimize.");
        data.push_back(new_data);
        return writeBufferFile();
    }

    if (new_data.cmd == 'W') {
        bool optimize_applied = false;

        if (optimize_applied = ignoreDupWrite(new_data, new_data.index, new_data.index)) {  // Opt1
            LOG("Ignore Duplicated Write Optimization (#1) Applied.");
        }

        optimize_applied = false;
        if (optimize_applied = narrowEraseRangeSeveralTimes(new_data)) {  // Opt 4
            LOG("Narrow Erase Range Optimization (#4) Applied.");
        }
    }
    if (new_data.cmd == 'E') {
        bool optimize_applied = false;

        if (optimize_applied = ignoreDupWrite(new_data, new_data.index, new_data.getLastIndex())) {  // Opt2
            LOG("Ignore Duplicated Write Optimization (#2) Applied.");
        }

        optimize_applied = false;
        if (optimize_applied = mergeLastErase(new_data)) {  // Opt3
            LOG("Merge with Last Erase Optimization (#3) Applied.");
        }
    }

    return writeBufferFile();
}

bool CommandBuffer::narrowEraseRangeSeveralTimes(BufferData& new_data) {
    bool has_change_in_data = false;
    if (has_change_in_data = narrowEraseRange(new_data, data.size())) {
        for (int i = data.size() - 1; i >= 0; i--) {
            if (data[i].cmd == 'W') {
                narrowEraseRange(data[i], i);
            }
        }
    }
    data.push_back(new_data);
    return has_change_in_data;
}

bool CommandBuffer::narrowEraseRange(BufferData& write_data,
                                     int write_data_pos) {
    bool has_change_in_data = false;

    for (int i = write_data_pos - 1; i >= 0; i--) {
        if (data[i].cmd != 'E') {
            continue;
        }

        bool invalid_erase_data = false;
        if (data[i].index == write_data.index) {
            has_change_in_data = true;
            if (data[i].index == 99) {
                invalid_erase_data = true;
            } else {
                data[i].index++;
                data[i].erase_size--;
            }
        } else if (data[i].getLastIndex() == write_data.index) {
            has_change_in_data = true;
            data[i].erase_size--;
        } else {
            continue;
        }
        invalid_erase_data |= data[i].erase_size <= 0;

        if (invalid_erase_data == true) {
            data.erase(data.begin() + i);
        }
    }

    return has_change_in_data;
}

bool CommandBuffer::ignoreDupWrite(BufferData& new_data, int left, int right) {
    bool has_change_in_data = false;

    for (int i = data.size() - 1; i >= 0; i--) {
        if (data[i].cmd == 'W' &&
            left <= data[i].index && data[i].index <= right) {
            data.erase(data.begin() + i);
            has_change_in_data = true;
        }
    }
    return has_change_in_data;
}

bool CommandBuffer::mergeLastErase(BufferData& new_data) {
    if (data.empty()) {
        data.push_back(new_data);
        return false;
    }

    BufferData& tail_data = data[data.size() - 1];
    if (tail_data.cmd != 'E') {
        data.push_back(new_data);
        return false;
    }

    BufferData left_data = new_data < tail_data ? new_data : tail_data;
    BufferData right_data = new_data < tail_data ? tail_data : new_data;

    if (right_data.index <= left_data.getLastIndex() + 1) {
        const int MAX_ERASE_SIZE = 10;
        int collapsed_erase_size = right_data.getLastIndex() -
                                   left_data.index + 1;

        data.erase(data.end() - 1);

        if (collapsed_erase_size > MAX_ERASE_SIZE) {
            data.push_back(
                BufferData{'E', left_data.index, "", MAX_ERASE_SIZE });
            data.push_back(
                BufferData{'E', left_data.index + MAX_ERASE_SIZE, "",
                           collapsed_erase_size - MAX_ERASE_SIZE });
            return true;
        } else {
            data.push_back(
                BufferData{ 'E', left_data.index, "", collapsed_erase_size });
            return true;
        }
    }

    data.push_back(new_data);
    return false;
}

bool CommandBuffer::isFullBuffer() {
    if (data.size() >= BUFFER_MAX) {
        return true;
    }
    return false;
}

std::vector<BufferData> CommandBuffer::flushBuffer() {
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
    std::fstream buffer_file(BUFFER_FILE_NAME);
    if (!buffer_file) {
        std::ofstream ofs(BUFFER_FILE_NAME);
        if (!ofs) {
            return false;
        }
    }
    return true;
}

bool CommandBuffer::readBufferFile() {
    std::fstream buffer_file(BUFFER_FILE_NAME, std::ios::in);
    if (!buffer_file) {
        return false;
    }

    /* read nand and store to the buffer */
    std::stringstream buffer;
    std::string cmd;
    buffer << buffer_file.rdbuf();

    std::string token;
    BufferData buf_data;

    // Split String with comma(,) as delimiter
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
        } else if (cmd[0] == 'E') {
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
    buffer_file.close();
    return true;
}

bool CommandBuffer::writeBufferFile() {
    std::ofstream buffer_file(BUFFER_FILE_NAME,
                              std::ios::out | std::ios::trunc);
    if (!buffer_file.is_open()) {
        return false;
    }

    std::string cmd_str = "";
    std::string space_str(1, SPACE_STRING);
    std::string delimeter_str(1, DELIMETER_STRING);

    buffer_file.seekp(0, std::ios::end);
    for (auto& cmd_data : data) {
        if (cmd_data.cmd == 'W') {
            cmd_str = "W" + space_str + std::to_string(cmd_data.index) +
                            space_str + cmd_data.write_value + delimeter_str;
            buffer_file << cmd_str;
        } else if (cmd_data.cmd == 'E') {
            cmd_str = "E" + space_str + std::to_string(cmd_data.index) +
                            space_str + std::to_string(cmd_data.erase_size) +
                            delimeter_str;
            buffer_file << cmd_str;
        }
    }

    buffer_file.close();
    return true;
}

bool CommandBuffer::flushBufferFile() {
    std::ofstream buffer_file(BUFFER_FILE_NAME,
                              std::ios::out | std::ios::trunc);
    if (!buffer_file.is_open()) {
        return false;
    }

    buffer_file.close();
    return true;
}
