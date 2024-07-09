/* Copyright 2024 Code Love you */

#include <stdexcept>
#include "SSDManager.h"

SSDManager::SSDManager(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        parsed_input.push_back(argv[i]);
    }

    //// TODO: Factory Pattern
    //file_manager = new FileManager();
    //ssd_writer = new SSDWriter(file_manager);
    //ssd_reader = new SSDReader(file_manager);
}

//SSDManager::~SSDManager() {
//    delete file_manager;
//    delete ssd_writer;
//    delete ssd_reader;
//}

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

//bool SSDManager::executeCommand() {
//    if (isValidInput() == false) {
//        return false;
//    }

//    std::string& cmd = parsed_input[1];
//    int index = convertIndexInt();

//    if (cmd == "R") {
//        return ssd_reader.read(NAND_FILE, RESULT_FILE, index);
//    }

//    if (cmd == "W") {
//        std::string& value = parsed_input[3];
//        return ssd_writer.write(NAND_FILE, index, value);
//    }
//}

std::vector<std::string> SSDManager::getParsedCommand() {
    return parsed_input;
}

bool SSDManager::isValidCommand(int argc) {
    if (argc < 2) {
        return false;
    }

    std::string cmd = parsed_input[1];
    if (cmd != "W" && cmd != "R") {
        return false;
    }

    return true;
}

bool SSDManager::isValidIndex(int argc) {
    if (argc < 3) {
        return false;
    }

    std::string& index = parsed_input[2];
    try {
        if (stoi(index) < 0 || stoi(index) > 99) {
            return false;
        }
    }
    catch (std::exception& e) {  // stoi() fail
        return false;
    }

    return true;
}

bool SSDManager::isValidReadInput(int argc) {
    std::string& cmd = parsed_input[1];

    if (cmd == "R" && argc != 3) {
        return false;
    }

    return true;
}

bool SSDManager::isValidWriteInput(int argc) {
    std::string& cmd = parsed_input[1];

    if (cmd == "W") {
        if (argc != 4) {
            return false;
        }

        std::string& value = parsed_input[3];
        if (value.length() != 10) {
            return false;
        }
        if (value.substr(0, 2) != "0x") {
            return false;
        }
        for (char& c : value.substr(2, 8)) {
            if (c < '0' || (c > '9' && c < 'A') || c > 'F') {
                return false;
            }
        }
    }

    return true;
}

int SSDManager::convertIndexInt() {
    return stoi(parsed_input[2]);
}

