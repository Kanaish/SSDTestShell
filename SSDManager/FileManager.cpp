/* Copyright 2024 Code Love you */

#include <iostream>
#include <fstream>
#include "FileManager.h"

FileManager::FileManager() {
}

bool FileManager::init(std::string name) {
    return true;
}

bool FileManager::open(std::string name) {
    return true;
}

bool FileManager::close(std::string name) {
    return true;
}

std::string FileManager::read(std::string name, int index) {
    return "";
}

bool FileManager::write(std::string name, int index, std::string value) {
    
    nandFile.open("nand.txt", std::ios::out | std::ios::in | std::ios::ate);
    
    if (nandFile.is_open())
    {
        return true;
    }
    else
    {
        std::cout << "Open Failed\n";
        /* TO DO : implement exception with throw */
        return false;
    }
    nandFile.close();
    return true;
}

bool FileManager::write(std::string name, std::string value) {
    return true;
}