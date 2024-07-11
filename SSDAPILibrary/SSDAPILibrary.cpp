/* Copyright 2024 Code Love you */

#include "pch.h"
#include "SSDAPILibrary.h"
#include "FileManager.h"

static const int SSD_START_INDEX = 0;
static const int SSD_LAST_INDEX = 99;
static const int ERASE_MAX_SIZE = 100;
static const int ERASE_MAX_SIZE_FOR_SSD = 10;

static const int SYSTEM_ERROR = -1;
static const int INVALID_ARGUMENT = -2;
static const int INVALID_COMMAND = -3;
static const int TEST_FAIL = -4;

static bool isValidLBA(const std::string& str) {
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

static bool isValidSize(const std::string& str) {
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

static bool isValidAddress(const std::string& str) {
    if (str.size() != 10 || str.substr(0, 2) != "0x") return false;
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

static int doErase(int start_lba, int size) {
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

int SSDAPIWrite(const char* arg) {
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

int SSDAPIRead(const char* arg, bool isPrint) {
    std::istringstream iss(arg);
    std::string first_word, second_word;
    FileManager* file_manager = new FileManager();

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
        std::cout << file_manager->read("../../resources/result.txt")
            << std::endl;
    }

    return 0;
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
    for (int i = 0; i < 100; ++i) {
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
    for (int i = 0; i < 100; ++i) {
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
    std::string cmd = "SSDManager.exe f";
    int ret = system(cmd.c_str());
    if (ret != 0) {
        return -1;
    }
    return 0;
}
