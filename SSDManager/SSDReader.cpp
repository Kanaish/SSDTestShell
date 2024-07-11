/* Copyright 2024 Code Love you */
#include <iostream>
#include "SSDReader.h"

bool SSDReader::read(const std::string& nand_file,
    const std::string& result_file, int index) {
    LOG("SSD Read is started");
    std::string result = readSSDValue(nand_file, index);
    if (result == "") {
        return false;
    }
    LOG("SSD Read is completed");
    return writeResultValue(result_file, result);
}

std::string SSDReader::readSSDValue(const std::string& nand_file, int index) {
    LOG("SSD Nand Read is started");
    try {
        return fm->read(nand_file, index);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << ":nand_file\n";
        return "";
    }
    LOG("SSD Nand Read is completed");
}

bool SSDReader::writeResultValue(const std::string& result_file,
    std::string& result) {
    LOG("SSD Result write is started");
    try {
        return fm->write(result_file, result);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << ":result_file\n";
        return false;
    }
    LOG("SSD Result write is completed");
}
