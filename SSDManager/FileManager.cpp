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

unsigned int FileManager::read(std::string name, int index) {
    return 0;
}

bool FileManager::write(std::string name, int index, unsigned int value) {
    return true;
}

bool FileManager::write(std::string name, unsigned int value) {
    return true;
}


