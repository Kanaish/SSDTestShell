/* Copyright 2024 Code Love you */
#pragma once
#include<string>
#include "FileManager.h"

class SSDWriter {
 public:
    explicit SSDWriter(FileManagerInterface* file_mgr);
    bool write(std::string nand_file, int index, std::string value);
 private:
    FileManagerInterface* file_mgr;
    const std::string CLASS_NAME = "SSDWriter";
};
