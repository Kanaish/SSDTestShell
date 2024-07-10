/* Copyright 2024 Code Love you */
#include <iostream>
#include "SSDReader.h"

bool SSDReader::read(const std::string& nand_file,
    const std::string& result_file, int index) {
    std::string result = readSSDValue(nand_file, index);
    if (result == "") {
        return false;
    }

    return writeResultValue(result_file, result);
}

std::string SSDReader::readSSDValue(const std::string& nand_file, int index) {
    try {
        return fm->read(nand_file, index);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << ":nand_file\n";
        return "";
    }
}

bool SSDReader::writeResultValue(const std::string& result_file,
    std::string& result) {

    try {
        return fm->write(result_file, result);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << ":result_file\n";
        return false;
    }
}


