/* Copyright 2024 Code Love you */

#include <iostream>
#include <fstream>
#include "FileManager.h"

FileManager::FileManager() {
}

std::string FileManager::read(std::string name, int index) {
    return "";
}

bool FileManager::write(std::string name, int index, std::string value) {

    std::fstream nandFile(name, std::ios::in | std::ios::out);

    if (nandFile.is_open())
    {
        nandFile.seekg(0, std::ios::end);
        nandFile << "LBA" << index << " " << value << " ";
    }
    else
    {
        /* TO DO : implement exception with throw */
        return false;
    }
    nandFile.close();
    return true;
}

bool FileManager::write(std::string name, std::string value) {
    return true;
}