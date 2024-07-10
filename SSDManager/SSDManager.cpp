/* Copyright 2024 Code Love you */

#include "SSDManager.h"

SSDManager::SSDManager(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        parsed_input.push_back(argv[i]);
    }

    parsed_input_arg_cnt = argc;

    // TODO: Factory Pattern
    file_manager = new FileManager();
    ssd_writer = new SSDWriter(file_manager);
    ssd_reader = new SSDReader(file_manager);
}

SSDManager::~SSDManager() {
    delete file_manager;
    delete ssd_writer;
    delete ssd_reader;
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

    return true;
}

bool SSDManager::executeCommand() {
    if (isValidInput() == false) {
        return false;
    }

    if (cmd == 'R') {
        return ssd_reader->read(NAND_FILE, RESULT_FILE, index);
    }

    if (cmd == 'W') {
        return ssd_writer->write(NAND_FILE, index, value);
    }

    return false;
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
    if (cmd != 'W' && cmd != 'R') {
        return false;
    }

    return true;
}

bool SSDManager::isValidIndex() {
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

    return true;
}

bool SSDManager::isValidWriteInput() {
    if (cmd == 'W') {
        value = parsed_input[3];

        if (value.length() != 10) {
            return false;
        }
        if (value[0] != '0') {
            return false;
        }
        if (std::toupper(value[1]) != 'X') {
            return false;
        }
        for (char& c : value.substr(2, 8)) {
            if (std::isxdigit(c) == false) {
                return false;
            }
        }
    }

    return true;
}
