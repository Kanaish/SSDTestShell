/* Copyright 2024 Code Love you */

#include <vector>
#include <string>
#include "SSDManager.h"
#include "LogManager.h"

SSDManager::SSDManager(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        parsed_input.push_back(argv[i]);
    }

    parsed_input_arg_cnt = argc;

    file_manager = new FileManager();
    ssd_writer = new SSDWriter(file_manager);
    ssd_reader = new SSDReader(file_manager);
    ssd_eraser = new SSDEraser(file_manager);
    command_buffer = new CommandBuffer();
}

SSDManager::~SSDManager() {
    delete file_manager;
    delete ssd_writer;
    delete ssd_reader;
    delete ssd_eraser;
    delete command_buffer;
}

bool SSDManager::isValidInput() {
    if (isValidCommand() == false) {
        return false;
    }

    if (isValidIndex() == false) {
        return false;
    }

    if (isValidArgCnt() == false) {
        return false;
    }

    if (isValidWriteInput() == false) {
        return false;
    }

    if (isValidEraseInput() == false) {
        return false;
    }

    return true;
}

bool SSDManager::executeCommand() {
    if (isValidInput() == false) {
        LOG("Invalid Command Is Entered.");
        return false;
    }

    if (cmd == 'R') {
        std::string buffer_ret = command_buffer->findMatchedWrite(index);
        if (buffer_ret == "") {
            buffer_ret = command_buffer->findMatchedErase(index);
        }
        if (buffer_ret == "") {
            return ssd_reader->read(NAND_FILE, RESULT_FILE, index);
        }
        try {
            return file_manager->write(RESULT_FILE, buffer_ret);
        }
        catch (std::exception& e) {
            return false;
        }
    }

    std::vector<BufferData> flushed_data;

    if (cmd == 'W' || cmd == 'E') {
        BufferData data{ cmd, index, write_value, erase_size };

        if (command_buffer->updateBuffer(data) == false) {
            return false;
        }

        if (command_buffer->isFullBuffer()) {
            LOG("Buffer is full. Auto Flush Executed.");
            flushed_data = command_buffer->flushBuffer();
        }
    }

    if (cmd == 'F') {
        LOG("Manual Flush Executed.");
        flushed_data = command_buffer->flushBuffer();
    }

    for (BufferData& data : flushed_data) {
        if (data.cmd == 'W') {
            if (ssd_writer->write(NAND_FILE, data.index,
                                             data.write_value) == false) {
                return false;
            }
        }
        if (data.cmd == 'E') {
            if (ssd_eraser->erase(NAND_FILE, data.index,
                                             data.erase_size) == false) {
                return false;
            }
        }
    }

    if (flushed_data.empty() == false) {
        return command_buffer->flushBufferFile();
    }
    return true;
}

std::vector<std::string> SSDManager::getParsedInput() {
    return parsed_input;
}

bool SSDManager::isValidCommand() {
    if (parsed_input_arg_cnt < 2) {
        return false;
    }

    std::string& cmd_str = parsed_input[1];

    if (cmd_str.length() > 1) {
        return false;
    }
    if (std::isalpha(cmd_str[0]) == false) {
        return false;
    }

    cmd = std::toupper(cmd_str[0]);
    if (cmd != 'W' && cmd != 'R' && cmd != 'E' && cmd != 'F') {
        return false;
    }

    return true;
}

bool SSDManager::isValidIndex() {
    if (cmd == 'F') {
        return true;
    }

    if (parsed_input_arg_cnt < 3) {
        return false;
    }

    std::string& index_str = parsed_input[2];
    for (char& c : index_str) {
        if (std::isdigit(c) == false) {
            return false;
        }
    }

    index = stoi(index_str);
    if (index < 0 || index > 99) {
        return false;
    }

    return true;
}

bool SSDManager::isValidArgCnt() {
    if (cmd == 'R' && parsed_input_arg_cnt != 3) {
        return false;
    }
    if (cmd == 'W' && parsed_input_arg_cnt != 4) {
        return false;
    }
    if (cmd == 'E' && parsed_input_arg_cnt != 4) {
        return false;
    }
    if (cmd == 'F' && parsed_input_arg_cnt != 2) {
        return false;
    }

    return true;
}

bool SSDManager::isValidWriteInput() {
    if (cmd == 'W') {
        write_value = parsed_input[3];

        if (write_value.length() != 10) {
            return false;
        }
        if (write_value[0] != '0') {
            return false;
        }
        if (std::toupper(write_value[1]) != 'X') {
            return false;
        }
        for (char& c : write_value.substr(2, 8)) {
            if (std::isxdigit(c) == false) {
                return false;
            }
        }

        write_value = convertToUpperValue(write_value);
    }

    return true;
}

std::string SSDManager::convertToUpperValue(std::string& str) {
    char upper_char_arr[11] = {};
    int i = 0;

    for (char& c : str) {
        upper_char_arr[i++] = std::isalpha(c) ? std::toupper(c) : c;
    }
    upper_char_arr[1] = 'x';
    upper_char_arr[i] = '\0';

    std::string upper_str = upper_char_arr;
    return upper_str;
}

bool SSDManager::isValidEraseInput() {
    if (cmd == 'E') {
        std::string& erase_size_str = parsed_input[3];

        for (char& c : erase_size_str) {
            if (std::isdigit(c) == false) {
                return false;
            }
        }


        erase_size = stoi(erase_size_str);

        if (erase_size > 10) {
            erase_size = 10;
        }
        if (index + erase_size > 99) {
            erase_size = 99 - index + 1;
        }

        return true;
    }

    return true;
}
