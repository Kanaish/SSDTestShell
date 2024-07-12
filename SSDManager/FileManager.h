/* Copyright 2024 Code Love you */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "FileManagerInterface.h"
#include "LogManager.h"
class FileManager : public FileManagerInterface {
 public:
    FileManager();
    std::string read(std::string name, int index);
    std::string read(std::string name);
    bool write(std::string name, int index, std::string value);
    bool write(std::string name, std::string value);
 private:
    std::string generateToken(int index);
    std::string generateMemoryBlock(std::string token, std::string value);
    const std::string EMPTY = "0x00000000";
    const int VALUE_LEN = 10;
    const std::string CLASS_NAME = "FileManager";
};
