/* Copyright 2024 Code Love you */

#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include "TestShell.h"

void TestShell::run(void) {
    std::string input_str;

    while (1) {
        std::getline(std::cin, input_str);
        if (input_str.empty()) continue;
        if (input_str.substr(0, 8) == TEST_SCENARIO_NAME) {
            try {
                runScenarioFile(input_str);
            }
            catch (const std::exception& e) {
                std::cerr << "Error running scenario file: " << e.what() << std::endl;
            }
        }
        else {
            try {
                this->execute(input_str);
            }
            catch (std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

bool TestShell::isValidCommand(const std::string& cmd) {
    return commandMap.find(cmd) != commandMap.end();
}

bool TestShell::isValidLBA(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }

    int index = std::stoi(str);
    if (index < SSD_START_INDEX || index > SSD_LAST_INDEX) {
        return false;
    }

    return true;
}

bool TestShell::isValidSize(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }

    int index = std::stoi(str);
    if (index < SSD_START_INDEX || index > ERASE_MAX_SIZE) {
        return false;
    }

    return true;
}

bool TestShell::isValidAddress(const std::string& str) {
    if (str.size() != 10 || str.substr(0, 2) != "0x") return false;
    for (size_t i = 2; i < str.size(); ++i) {
        if (!std::isxdigit(str[i])) return false;
    }
    return true;
}

bool TestShell::isValidArgument(const std::string& arg) {
    std::istringstream iss(arg);
    std::string first_word, second_word, third_word;

    if (!(iss >> first_word)) return false;
    if (!isValidLBA(first_word)) return false;

    if (!(iss >> second_word)) return false;
    if (!isValidAddress(second_word)) return false;

    if ((iss >> third_word)) return false;

    return true;
}

int TestShell::execute(std::string input_str, bool fromScenarioFile) {
    size_t pos = input_str.find(' ');
    std::string cmd = (pos == std::string::npos) ?
        input_str : input_str.substr(0, pos);
    std::string arg = (pos == std::string::npos) ?
        "" : input_str.substr(pos + 1);

    if (!isValidCommand(cmd)) {
        throw std::invalid_argument("INVALID COMMAND");
    }

    if (cmd == "fullread" || cmd == "exit" || cmd == "help"
        || cmd == "testapp1" || cmd == "testapp2" || cmd =="flush") {
        if (!arg.empty()) {
            throw std::invalid_argument("INVALID COMMAND");
        }
    }

    int ret = commandMap.at(cmd)(arg);
    
    if (ret != 0) {
        if (fromScenarioFile) {
            return -1;
        }
        switch (ret) {
        case (SYSTEM_ERROR):
            throw std::invalid_argument("SYSTEM_ERROR");
        case (INVALID_ARGUMENT):
            throw std::invalid_argument("INVALID ARGUMENT");
        case (INVALID_COMMAND) :
            throw std::invalid_argument("INVALID COMMAND");
        case (TEST_FAIL) : 
            throw std::invalid_argument("TEST FAIL");
        default:
            throw std::invalid_argument("error");
        }
    }
    return ret;
}

int TestShell::write(const std::string& arg) {
    std::string cmd = "SSDManager.exe w ";
    int ret;

    if (!isValidArgument(arg)) {
        return INVALID_COMMAND;
    }
    cmd += arg;

    ret = system(cmd.c_str());
    if (ret != 0) {
        return SYSTEM_ERROR;
    }
    return 0;
}

int TestShell::read(const std::string& arg, bool isPrint) {
    std::istringstream iss(arg);
    std::string first_word, second_word;

    if (!(iss >> first_word)) {
        return INVALID_COMMAND;
    }
    if ((iss >> second_word)) {
        return INVALID_COMMAND;
    }

    if (!isValidLBA(first_word)) {
        return INVALID_COMMAND;
    }

    std::string cmd = "SSDManager.exe r ";
    int ret;

    cmd += arg;

    ret = system(cmd.c_str());
    if (ret != 0) {
        return SYSTEM_ERROR;
    }

    if (isPrint) {
        std::cout << file_manager->read("../../resources/result.txt") << std::endl;
    }

    return 0;
}

int TestShell::exit() {
    std::exit(0);
    return 0;
}

int TestShell::help() {
    std::cout << file_manager->read("../../resources/help.txt") << std::endl;
    return 0;
}

int TestShell::fullWrite(const std::string& arg) {
    std::istringstream iss(arg);
    std::string first_word, second_word;

    if (!(iss >> first_word)) {
        return INVALID_COMMAND;
    }
    if ((iss >> second_word)) {
        return INVALID_COMMAND;
    }
    if (!isValidAddress(first_word)) {
        return INVALID_COMMAND;
    }

    int ret = 0;
    for (int i = 0; i < 100; ++i) {
        std::string cmd;
        cmd = std::to_string(i) + " " + first_word;
        ret = this->write(cmd);
        if (ret != 0) {
            return ret;
        }
    }
    return ret;
}

int TestShell::fullRead() {
    int ret = 0;
    for (int i = 0; i < 100; ++i) {
        std::string cmd;

        cmd = std::to_string(i) + " ";
        ret = this->read(cmd);
        if (ret != 0) {
            return ret;
        }
    }

    return ret;
}

int TestShell::testApp1(void) {
    std::string write_value = "0xAAAABBBB";
    int ret = 0;
    ret = fullWrite(write_value);
    if (ret != 0) {
        return ret;
    }

    for (int lba = 0; lba < 100; lba++) {
        ret = read(std::to_string(lba), false);
        if (ret != 0) {
            return ret;
        }

        std::string line = file_manager->read("../../resources/result.txt");
        if (line != write_value) {
            ret = TEST_FAIL;
            break;
        }
    }
    return ret;
}

int TestShell::testApp2(void) {
    std::string write_value = "0xAAAABBBB";
    int ret = 0;
    for (int i = 0; i < 30; ++i) {
        for (int lba = 0; lba <= 5; ++lba) {
            std::string arg = std::to_string(lba) + " " + write_value;
            ret = write(arg);
            if (ret != 0) {
                return ret;
            }
        }
    }

    write_value = "0x12345678";
    for (int lba = 0; lba <= 5; ++lba) {
        std::string arg = std::to_string(lba) + " " + write_value;
        ret = write(arg);
        if (ret != 0) {
            return ret;
        }
    }

    for (int lba = 0; lba <= 5; ++lba) {
        ret = read(std::to_string(lba), false);
        if (ret != 0) {
            return ret;
        }
        std::string line = file_manager->read("../../resources/result.txt");
        if (line != write_value) {
            ret = TEST_FAIL;
            break;
        }
    }
    return ret;
}

int TestShell::doErase(int start_lba, int size) {
    int ret = 0;

    if (start_lba + size >= 100)
        size = 100 - start_lba;

    while (size >= 10) {
        std::string cmd = "SSDManager.exe e ";
        cmd += std::to_string(start_lba) + " " + std::to_string(10);

        ret = system(cmd.c_str());
        if (ret != 0) {
            return SYSTEM_ERROR;
        }

        size -= 10;
        start_lba += 10;
    }

    if (size != 0) {
        std::string cmd = "SSDManager.exe e ";
        cmd += std::to_string(start_lba) + " " + std::to_string(size);

        ret = system(cmd.c_str());
        if (ret != 0) {
            return SYSTEM_ERROR;
        }
    }

    return ret;
}

int TestShell::transStringtoIntInt(const std::string& arg,
    int* left_arg, int* right_arg) {
    std::istringstream iss(arg);
    std::string first_word, second_word, third_word;

    if (!(iss >> first_word))
        return INVALID_ARGUMENT;
    if (!isValidLBA(first_word))
        return INVALID_ARGUMENT;

    if (!(iss >> second_word))
        return INVALID_ARGUMENT;
    if (!isValidSize(second_word))
        return INVALID_ARGUMENT;

    if ((iss >> third_word))
        return INVALID_ARGUMENT;

    *left_arg = std::stoi(first_word);
    *right_arg = std::stoi(second_word);

    return 0;
}

int TestShell::erase(const std::string& arg) {
    int start_lba, size;
    int ret = 0;
    ret  = transStringtoIntInt(arg, &start_lba, &size);
    if (ret != 0) {
        return ret;
    }

    return doErase(start_lba, size);
}

int TestShell::erase_range(const std::string& arg) {
    int start_lba, end_lba;
    int ret = 0;
    ret = transStringtoIntInt(arg, &start_lba, &end_lba);
    if (ret != 0) {
        return ret;
    }

    if (start_lba >= end_lba)
        return INVALID_ARGUMENT;

    int size = end_lba - start_lba;

    return doErase(start_lba, size);
}

void TestShell::runScenarioFile(const std::string& filename) {
    try {
        std::string fullPath = "../../resources/" + filename;
        std::string file_content = file_manager->read(fullPath);
        if (file_content.empty()) {
            throw std::runtime_error("File is not opened or is empty");
        }

        std::istringstream infile(file_content);
        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) continue;

            std::cout << line << " --- Run...";
            int result = execute(line, true);
            if (result != 0) {
                std::cout << "FAIL!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::exit(1);
            }
            else std::cout << "Pass" << std::endl;
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error reading file: " << filename << " - " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error executing command from file: " << filename << " - " << e.what() << std::endl;
    }
}

int TestShell::flush(void) {
    std::string cmd = "SSDManager.exe f";

    int ret = system(cmd.c_str());
    if (ret != 0) {
        return SYSTEM_ERROR;
    }
    return 0;
}
