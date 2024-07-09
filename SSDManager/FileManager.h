/* Copyright 2024 Code Love you */
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "FileManagerInterface.h"

class FileManager : public FileManagerInterface {
public:
    FileManager();
    bool init(std::string name);
    bool open(std::string name);
    bool close(std::string name);
    unsigned int read(std::string name, int index);
    bool write(std::string name, int index, unsigned int value);
    bool write(std::string name, unsigned int value);
private:
    const std::string EMPTY = "0x00000000";
    const int MAX_SIZE = 100;
    const std::string RESULT = "result.txt";
    const std::string nand = "nand.txt";
};