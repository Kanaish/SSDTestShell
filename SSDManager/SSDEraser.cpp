/* Copyright 2024 Code Love you */
#include <iostream>
#include <stdexcept>
#include "SSDEraser.h"

SSDEraser::SSDEraser(FileManagerInterface* fm) :file_mgr{ fm } {}
bool  SSDEraser::erase(const std::string& nand_file, int index, int size) {
    try {
        for (int i = 0; i < size; i++) {
            if (file_mgr->write(nand_file, index + i, INIT_VALUE) == false)  return false ;
        }
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught standard exception: " << e.what() << std::endl;
        return false;
    }
}

void SSDEraser::getLogManagerInstance(LogManager* plm)
{
    this->lm = plm;
}