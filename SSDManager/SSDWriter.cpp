//    "Copyright [2024] <YD>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "SSDWriter.h"

SSDWriter::SSDWriter(FileManagerInterface* fm) :file_mgr{ fm } {}
bool  SSDWriter::writer(std::string nand_file, int index, std::string value) {
    try {
        return file_mgr->write(nand_file, index, value);
    }
    catch (const std::exception& e) {
        std::cerr << "Caught standard exception: " << e.what() << std::endl;
        return false;
    }
}
