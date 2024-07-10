/* Copyright 2024 Code Love you */

#include "SSDManager.h"

SSDManager::SSDManager(int argc, char** argv, LogManager * plm) {
    for (int i = 0; i < argc; i++) {
        parsed_input.push_back(argv[i]);
    }

    parsed_input_arg_cnt = argc;
    getLogManagerInstance(plm);
    // TODO: Factory Pattern
    file_manager = new FileManager();
    ssd_writer = new SSDWriter(file_manager);
    ssd_reader = new SSDReader(file_manager);
    ssd_eraser = new SSDEraser(file_manager);

    file_manager->getLogManagerInstance(plm);
    ssd_writer->getLogManagerInstance(plm);
    ssd_reader->getLogManagerInstance(plm);
    ssd_eraser->getLogManagerInstance(plm);
}

SSDManager::~SSDManager() {
    delete file_manager;
    delete ssd_writer;
    delete ssd_reader;
    delete ssd_eraser;
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
        return false;
    }

    if (cmd == 'R') {
        return ssd_reader->read(NAND_FILE, RESULT_FILE, index);
    }
    if (cmd == 'W') {
        return ssd_writer->write(NAND_FILE, index, write_value);
    }
    if (cmd == 'E') {
        return ssd_eraser->erase(NAND_FILE, index, erase_size);
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
    if (cmd != 'W' && cmd != 'R' && cmd != 'E') {
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
    if (cmd == 'E' && parsed_input_arg_cnt != 4) {
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
    }

    return true;
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

void SSDManager::getLogManagerInstance(LogManager* plm)
{
    this->lm = plm;
}
