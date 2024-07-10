/* Copyright 2024 Code Love you */
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "FileManagerInterface.h"

class FileManager : public FileManagerInterface {
public:
    FileManager();
    std::string read(std::string name, int index);
    bool write(std::string name, int index, std::string value);
    bool write(std::string name, std::string value);
    std::string read(std::string name);
private:
    const std::string EMPTY = "0x00000000";
    const int VALUE_LEN = 10;
    const std::string RESULT = "result.txt";
    const std::string NAND = "nand.txt";
};