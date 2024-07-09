#pragma once
#include <iostream>
#include <fstream>
#include <string>

class FileManager {
public:
    FileManager();
    std::fstream* init(std::string name);
    std::fstream* open(std::string name);
    unsigned int read(std::fstream* fs, int index);
    bool write(std::fstream* fs, int index, unsigned int value);
    bool write(std::fstream* fs, unsigned int value);
    bool close(std::fstream* fs);
    
};