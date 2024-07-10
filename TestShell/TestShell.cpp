/* Copyright 2024 Code Love you */

#include <iostream>
#include <sstream>
#include <fstream>
#include "TestShell.h"

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
    std::cout << file_manager->read("../../resources/result.txt") << std::endl;

    return 0;
}

void TestShell::exit() {
    std::exit(0);
}

void TestShell::help() {

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

    for (int lba = 0; lba < 100; lba++) {
        if (read(std::to_string(lba)) == -1) {
            return -1;
        }

        std::string result = file_manager->read("../../resources/result.txt");
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
        std::string result = file_manager->read("../../resources/result.txt");
        if (result != write_value) {
            test_passed = false;
            break;
        }
    }
    return 0;
}
