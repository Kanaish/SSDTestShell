/* Copyright 2024 Code Love you */

#include "SSDManager.h"

SSDManager::SSDManager(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        parsed_input.push_back(argv[i]);
    }

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
    int argc = static_cast<int>(parsed_input.size());

    if (isValidCommand(argc) == false) {
        return false;
    }

    if (isValidIndex(argc) == false) {
        return false;
    }

    if (isValidWriteInput(argc) == false) {
        return false;
    }

    if (isValidReadInput(argc) == false) {
        return false;
    }

    return true;
}

bool SSDManager::executeCommand() {
    if (isValidInput() == false) {
        return false;
    }

    std::string& cmd = parsed_input[1];
    char cmdCode = std::toupper(cmd[0]);

    int index = convertIndexInt();

    if (cmdCode == 'R') {
        return ssd_reader->read(NAND_FILE, RESULT_FILE, index);
    }

    if (cmdCode == 'W') {
        std::string& value = parsed_input[3];
        return ssd_writer->write(NAND_FILE, index, value);
    }

    return false;
}

std::vector<std::string> SSDManager::getParsedCommand() {
    return parsed_input;
}

bool SSDManager::isValidCommand(int argc) {
    if (argc < 2) {
        return false;
    }

    std::string& cmd = parsed_input[1];

    if (cmd.length() > 1) {
        return false;
    }
    if (std::isalpha(cmd[0]) == false) {
        return false;
    }

    char cmdCode = std::toupper(cmd[0]);
    if (cmdCode != 'W' && cmdCode != 'R') {
        return false;
    }

    return true;
}

bool SSDManager::isValidIndex(int argc) {
    if (argc < 3) {
        return false;
    }

    std::string& index = parsed_input[2];

    for (char& c : index) {
        if (std::isdigit(c) == false) {
            return false;
        }
    }

    if (stoi(index) < 0 || stoi(index) > 99) {
        return false;
    }

    return true;
}

bool SSDManager::isValidReadInput(int argc) {
    std::string& cmd = parsed_input[1];
    char cmdCode = std::toupper(cmd[0]);

    if (cmdCode == 'R' && argc != 3) {
        return false;
    }

    return true;
}

bool SSDManager::isValidWriteInput(int argc) {
    std::string& cmd = parsed_input[1];
    char cmdCode = std::toupper(cmd[0]);

    if (cmdCode == 'W') {
        if (argc != 4) {
            return false;
        }

        std::string& value = parsed_input[3];
        if (value.length() != 10) {
            return false;
        }
        if (value.substr(0, 1) != "0") {
            return false;
        }
        if (std::toupper(value.substr(1, 1)[0]) != 'X') {
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

int SSDManager::convertIndexInt() {
    return stoi(parsed_input[2]);
}

