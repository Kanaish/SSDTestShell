/* Copyright 2024 Code Love you */
#include <iostream>
#include <stdexcept>
#include "SSDEraser.h"

SSDEraser::SSDEraser(FileManagerInterface* fm) :file_mgr{ fm } {}
bool  SSDEraser::erase(std::string nand_file, int index, int size) {
    try {
        bool ret = false;
        for (int i = 0; i < size; i++) {
            ret = file_mgr->write(nand_file, index + i, "0x00000000");
            if (ret == false)  return ret;
        }
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught standard exception: " << e.what() << std::endl;
        return false;
    }



}