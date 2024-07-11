/* Copyright 2024 Code Love you */
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "framework.h"
#include "SSDAPILibrary.h"
#include "LogManager.h"

static const int LBA_START_INDEX = 0;
static const int LBA_LAST_INDEX = 99;
static const int LBA_MIN_SIZE = 0;
static const int LBA_MAX_SIZE = 100;
static const int LBA_PROCESS_SIZE = 10;
static const int ADDRESS_LENGTH = 10;

static const int SYSTEM_ERROR = -1;
static const int INVALID_ARGUMENT = -2;
static const int INVALID_COMMAND = -3;
static const int TEST_FAIL = -4;

static bool isValidLBA(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }

    int lba = std::stoi(str);
    if (lba < LBA_START_INDEX || lba > LBA_LAST_INDEX) {
        return false;
    }

    return true;
}

static bool isValidSize(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }

    int index = std::stoi(str);
    if (index < LBA_MIN_SIZE || index > LBA_MAX_SIZE) {
        return false;
    }

    return true;
}

static bool isValidAddress(const std::string& str) {
    if (str.size() != ADDRESS_LENGTH || str.substr(0, 2) != "0x") return false;
    for (size_t i = 2; i < str.size(); ++i) {
        if (!std::isxdigit(str[i])) return false;
    }
    return true;
}

static bool isValidArgument(const std::string& arg) {
    std::istringstream iss(arg);
    std::string first_word, second_word, third_word;

    if (!(iss >> first_word)) return false;
    if (!isValidLBA(first_word)) return false;

    if (!(iss >> second_word)) return false;
    if (!isValidAddress(second_word)) return false;

    if ((iss >> third_word)) return false;

    return true;
}

static int transStringtoIntInt(const std::string& arg,
    int* left_value, int* right_value) {
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

    *left_value = std::stoi(first_word);
    *right_value = std::stoi(second_word);

    return 0;
}

static int doErase(int start_lba, int size) {
    int ret = 0;

    if (start_lba + size >= LBA_MAX_SIZE)
        size = LBA_MAX_SIZE - start_lba;

    while (size >= LBA_PROCESS_SIZE) {
        std::string cmd = ".\\SSDManager.exe e ";
        cmd += std::to_string(start_lba) + " " + std::to_string(10);

        ret = system(cmd.c_str());
        if (ret != 0) {
            return SYSTEM_ERROR;
        }

        size -= LBA_PROCESS_SIZE;
        start_lba += LBA_PROCESS_SIZE;
    }

    if (size > 0) {
        std::string cmd = ".\\SSDManager.exe e ";
        cmd += std::to_string(start_lba) + " " + std::to_string(size);

        ret = system(cmd.c_str());
        if (ret != 0) {
            return SYSTEM_ERROR;
        }
    }

    return ret;
}

int SSDAPIWrite(const char* arg) {
    std::string cmd = ".\\SSDManager.exe w ";
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

int SSDAPIRead(const char* arg, bool isPrint) {
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

    std::string cmd = ".\\SSDManager.exe r ";
    int ret;

    cmd += arg;

    ret = system(cmd.c_str());
    
    if (ret != 0) {
        return SYSTEM_ERROR;
    }

    if (isPrint) {
        cmd = "type ..\\..\\resources\\result.txt";
        ret = system(cmd.c_str());
        if (ret != 0) {
            return SYSTEM_ERROR;
        }
        std::cout << std::endl;
    }

    return ret;
}

int SSDAPIFullWrite(const char* arg) {
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
    for (int i = LBA_START_INDEX; i <= LBA_LAST_INDEX; ++i) {
        std::string cmd;
        cmd = std::to_string(i) + " " + first_word;
        ret = SSDAPIWrite(cmd.c_str());
        if (ret != 0) {
            return ret;
        }
    }
    return ret;
}

int SSDAPIFullRead(void) {
    int ret = 0;
    for (int i = LBA_START_INDEX; i <= LBA_LAST_INDEX; ++i) {
        std::string cmd;

        cmd = std::to_string(i) + " ";
        ret = SSDAPIRead(cmd.c_str(), true);
        if (ret != 0) {
            return ret;
        }
    }

    return ret;
}

int SSDAPIErase(const char* arg) {
    int start_lba, size;
    int ret = 0;
    ret = transStringtoIntInt(arg, &start_lba, &size);
    if (ret != 0) {
        return ret;
    }

    return doErase(start_lba, size);
}

int SSDAPIEraseRange(const char* arg) {
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

int SSDAPIFlush(void) {
    std::string cmd = ".\\SSDManager.exe f";
    int ret = system(cmd.c_str());
    if (ret != 0) {
        return -1;
    }
    return 0;
}
