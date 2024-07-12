/* Copyright 2024 Code Love you */

#pragma once
#include <string>
#include "FileManagerInterface.h"
#include "LogManager.h"
class SSDReader {
 public:
    explicit SSDReader(FileManagerInterface* fm) : fm(fm) {
    }
    bool read(const std::string& nand_file,
    const std::string& result_file, int index);
 private:
    bool writeResultValue(const std::string& result_file,
                          const std::string& result);
    std::string readSSDValue(const std::string& nand_file, int index);

    FileManagerInterface* fm;
    const std::string CLASS_NAME = "SSDReader";
};
