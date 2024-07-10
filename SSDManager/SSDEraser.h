/* Copyright 2024 Code Love you */
#pragma once
#include<string>
#include "FileManager.h"

class SSDEraser {
public:
    explicit SSDEraser(FileManagerInterface* file_mgr);
    bool erase(std::string nand_file, int index, int size);
private:
    FileManagerInterface* file_mgr;
};
