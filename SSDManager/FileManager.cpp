/* Copyright 2024 Code Love you */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "FileManager.h"

FileManager::FileManager() {
}

std::string FileManager::read(std::string name, int index) {
    std::fstream nandFile(name, std::ios::in | std::ios::out);
    std::string ret;
    if (nandFile.is_open())
    {
        std::stringstream buffer;
        buffer << nandFile.rdbuf();
        std::string tokenLba = std::string("LBA" + std::to_string(index));
        size_t pos = buffer.str().find(tokenLba);

        if (pos != std::string::npos) {
            size_t posValue = buffer.str().find(" ", pos);
            ret = buffer.str().substr(posValue + 1, VALUE_LEN);
        }
        else {
            ret = EMPTY;
        }
    }
    else {
        throw std::invalid_argument("File is not opened");
    }
    nandFile.close();
    return ret;

}

bool FileManager::write(std::string name, int index, std::string value) {

    std::fstream nandFile(name, std::ios::in | std::ios::out);

    if (nandFile.is_open()) {
        bool indexExistFlag = false;
        nandFile.seekp(0, std::ios::beg);

        std::stringstream buffer;
        buffer << nandFile.rdbuf();
        nandFile.seekp(0, std::ios::beg);
        std::string lba = std::string("LBA" + std::to_string(index));
        size_t pos = buffer.str().find(lba);

        if (pos != std::string::npos) {
            nandFile.seekp(pos, std::ios::beg);
            nandFile << "LBA" << index << " " << value << " ";
            indexExistFlag = true;
        }
        if (!indexExistFlag) {
            nandFile.seekg(0, std::ios::end);
            nandFile << "LBA" << index << " " << value << " ";
        }
    }
    else {
        throw std::invalid_argument("File is not opened");
        return false;
    }
    nandFile.close();
    return true;
}


bool FileManager::write(std::string name, std::string value) {
    return true;
}