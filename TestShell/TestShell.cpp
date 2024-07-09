/* Copyright 2024 Code Love you */

#include <sstream>

#include "TestShell.h"

void TestShell::run(void) {
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
    std::string first_word, second_word;

    if (!(iss >> first_word)) return false;
    if (!isValidIndex(first_word)) return false;

    if (!(iss >> second_word)) return false;
    if (!isValidAddress(second_word)) return false;

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

    commandMap.at(cmd)(arg);
}

int TestShell::write(const std::string& arg) {
    std::string cmd = "ssd.exe w ";
    int ret;

    if (!isValidArgument(arg)) {
        throw std::invalid_argument("INVALID COMMAND");
        return -1;
    }

    cmd += arg;

    ret = system(cmd.c_str());
    if (ret != 0) {
        throw std::invalid_argument("INVALID COMMAND");
        return ret;
    }
}

int TestShell::read(const std::string& arg) {
    std::string cmd = "ssd.exe r ";
    int ret;

    if (!isValidIndex(arg)) {
        throw std::invalid_argument("INVALID COMMAND");
        return -1;
    }

    cmd += arg;

    ret = system(cmd.c_str());
    if (ret != 0) {
        throw std::invalid_argument("INVALID COMMAND");
        return ret;
    }

    cmd = "type result.txt";

    ret = system(cmd.c_str());
    if (ret != 0) {
        throw std::invalid_argument("INVALID COMMAND");
        return ret;
    }

    return 0;
}

void TestShell::exit(void) {
}

void TestShell::help(void) {
}

int TestShell::fullWrite(const std::string& arg) {
    return 0;
}

int TestShell::fullRead(void) {
    return 0;
}
