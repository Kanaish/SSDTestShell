/* Copyright 2024 Code Love you */
#pragma once
#include<string>
#include "FileManager.h"

class SSDEraser {
public:
    explicit SSDEraser(FileManagerInterface* file_mgr);
    bool erase(const std::string& nand_file, int index, int size);
    void getLogManagerInstance(LogManager* plm);
private:
    FileManagerInterface* file_mgr;
    const std::string INIT_VALUE = "0x00000000";
    LogManager* lm;
};
