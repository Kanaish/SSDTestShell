/* Copyright 2024 Code Love you */

#include <iostream>
#include <sstream>
#include <fstream>

#include "TestShell.h"

#include "../SSDManager/FileManager.cpp"

void TestShell::run(void) {
    std::string input_str;

    while (1) {
        std::getline(std::cin, input_str);
        if (input_str.empty()) continue;

        try {
            this->execute(input_str);
        }
        catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

bool TestShell::isValidCommand(const std::string& cmd) {
    return commandMap.find(cmd) != commandMap.end();
}

bool TestShell::isValidIndex(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }

    int index = std::stoi(str);
    if (index < 0 || index > 99) {
        return false;
    }

    return true;
}

bool TestShell::isValidIndex2(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }

    int index = std::stoi(str);
    if (index < 0 || index > 100) {
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
    if (!isValidIndex(first_word)) return false;

    if (!(iss >> second_word)) return false;
    if (!isValidAddress(second_word)) return false;

    if ((iss >> third_word)) return false;

    return true;
}

void TestShell::execute(std::string input_str) {
    size_t pos = input_str.find(' ');
    std::string cmd = (pos == std::string::npos) ?
        input_str : input_str.substr(0, pos);
    std::string arg = (pos == std::string::npos) ?
        "" : input_str.substr(pos + 1);

    if (!isValidCommand(cmd)) {
        throw std::invalid_argument("INVALID COMMAND");
    }

    if (cmd == "fullread" || cmd == "exit" || cmd == "help" || cmd == "testapp1" || cmd == "testapp2") {
        if (!arg.empty()) {
            throw std::invalid_argument("INVALID COMMAND");
        }
    }

    commandMap.at(cmd)(arg);
}

int TestShell::write(const std::string& arg) {
    std::string cmd = "SSDManager.exe w ";
    int ret;

    if (!isValidArgument(arg)) {
        throw std::invalid_argument("INVALID COMMAND");
        return -1;
    }

    cmd += arg;

    ret = system(cmd.c_str());
    if (ret != 0) {
        throw std::invalid_argument("INVALID COMMAND");
    }

    return ret;
}

int TestShell::read(const std::string& arg) {
    std::istringstream iss(arg);
    std::string first_word, second_word;

    if (!(iss >> first_word)) throw std::invalid_argument("INVALID COMMAND");
    if ((iss >> second_word)) throw std::invalid_argument("INVALID COMMAND");
    if (!isValidIndex(first_word)) throw std::invalid_argument("INVALID COMMAND");

    std::string cmd = "SSDManager.exe r ";
    int ret;

    cmd += arg;

    ret = system(cmd.c_str());
    if (ret != 0) {
        throw std::invalid_argument("INVALID COMMAND");
        return ret;
    }

    FileManager* file_manager = new FileManager();
    std::cout << file_manager->read("../../resources/result.txt") << std::endl;

    return 0;
}

void TestShell::exit() {
    std::exit(0);
}

void TestShell::help() {
    FileManager* file_manager = new FileManager();

    std::cout << file_manager->read("../../resources/help.txt") << std::endl;
}

int TestShell::fullWrite(const std::string& arg) {
    std::istringstream iss(arg);
    std::string first_word, second_word;

    if (!(iss >> first_word)) throw std::invalid_argument("INVALID COMMAND");
    if ((iss >> second_word)) throw std::invalid_argument("INVALID COMMAND");
    if (!isValidAddress(first_word)) throw std::invalid_argument("INVALID COMMAND");

    for (int i = 0; i < 100; ++i) {
        std::string cmd;
        cmd = std::to_string(i) + " " + first_word;
        this->write(cmd);
    }

    return 0;
}

int TestShell::fullRead() {
    FileManager* file_manager = new FileManager();

    for (int i = 0; i < 100; ++i) {
        std::string cmd ;

        cmd = std::to_string(i) + " ";

        this->read(cmd);
    }

    return 0;
}

int TestShell::testApp1(void) {
    std::string write_value = "0xAAAABBBB"; // 임의의 값

    if (fullWrite(write_value) == -1) {
        return -1;
    }
    bool test_passed = true;
    FileManager file_manager;

    for (int lba = 0; lba < 100; lba++) {
        if (read(std::to_string(lba)) == -1) {
            return -1;
        }

        std::string result = file_manager.read("../../resources/result.txt");
        if (result != write_value) {
            test_passed = false;
            break;
        }
    }
    return 0;
}

int TestShell::testApp2(void) {
    std::string write_value = "0xAAAABBBB";

    for (int i = 0; i < 30; ++i) {
        for (int lba = 0; lba <= 5; ++lba) {
            std::string arg = std::to_string(lba) + " " + write_value;
            if (write(arg) != 0) {
                return -1;
            }
        }
    }

    write_value = "0x12345678";
    for (int lba = 0; lba <= 5; ++lba) {
        std::string arg = std::to_string(lba) + " " + write_value;
        if (write(arg) != 0) {
            return -1;
        }
    }

    for (int lba = 0; lba <= 5; ++lba) {
        if (read(std::to_string(lba)) == -1) {
            return -1;
        }
        bool test_passed = true;
        FileManager file_manager;
        std::string result = file_manager.read("../../resources/result.txt");
        if (result != write_value) {
            test_passed = false;
            break;
        }
    }
    return 0;
}

int TestShell::doErase(int& start_lba, int& size)
{
    int ret = 0;

    if (start_lba + size >= 100)
        size = 99 - start_lba;

    while (size > 10) {
        std::string cmd = "SSDManager.exe e ";
        cmd += std::to_string(start_lba) + " " + std::to_string(10);

        ret = system(cmd.c_str());
        if (ret != 0) {
            throw std::invalid_argument("INVALID SYSTEM COMMAND");
        }

        size -= 10;
        start_lba += 10;
    }

    if (size != 0) {
        std::string cmd = "SSDManager.exe e ";
        cmd += std::to_string(start_lba) + " " + std::to_string(size);

        ret = system(cmd.c_str());
        if (ret != 0) {
            throw std::invalid_argument("INVALID SYSTEM COMMAND");
        }
    }

    return ret;
}

int TestShell::erase(const std::string& arg) {
    std::istringstream iss(arg);
    std::string first_word, second_word, third_word;

    if (!(iss >> first_word))
        throw std::invalid_argument("INVALID ARGUMENT");
    if (!isValidIndex(first_word))
        throw std::invalid_argument("INVALID ARGUMENT");

    if (!(iss >> second_word))
        throw std::invalid_argument("INVALID ARGUMENT");
    if (!isValidIndex2(second_word))
        throw std::invalid_argument("INVALID ARGUMENT");

    if ((iss >> third_word))
        throw std::invalid_argument("INVALID ARGUMENT");

    int start_lba = std::stoi(first_word);
    int size = std::stoi(second_word);

    return doErase(start_lba, size);
}

int TestShell::erase_range(const std::string& arg) {
    std::istringstream iss(arg);
    std::string first_word, second_word, third_word;

    if (!(iss >> first_word))
        throw std::invalid_argument("INVALID ARGUMENT");
    if (!isValidIndex(first_word))
        throw std::invalid_argument("INVALID ARGUMENT");

    if (!(iss >> second_word))
        throw std::invalid_argument("INVALID ARGUMENT");
    if (!isValidIndex(second_word))
        throw std::invalid_argument("INVALID ARGUMENT");

    if ((iss >> third_word))
        throw std::invalid_argument("INVALID ARGUMENT");

    int start_lba = std::stoi(first_word);
    int end_lba = std::stoi(second_word);

    if (start_lba >= end_lba)
        throw std::invalid_argument("INVALID ARGUMENT");

    int size = end_lba - start_lba;

    return doErase(start_lba, size);
}