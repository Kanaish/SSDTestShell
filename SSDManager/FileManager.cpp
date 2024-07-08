/* Copyright 2024 Code Love you */

#include <iostream>
#include <fstream>
#include "FileManager.h"

FileManager::FileManager() {
}

std::fstream * FileManager::open(std::string) {
    return nullptr;
}

std::fstream* FileManager::init(std::string name) {
    return nullptr;
}

unsigned int FileManager::read(std::fstream* fs, int index) {
    return 0;
}

bool FileManager::write(std::fstream* fs, int index, unsigned int value) {
    return true;
}

bool FileManager::write(std::fstream* fs, unsigned int value) {
    return true;
}

bool FileManager::close(std::fstream* fs) {
    return true;
}
