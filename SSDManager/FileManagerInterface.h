/* Copyright 2024 Code Love you */
#pragma once
#include <string>

class FileManagerInterface {
public:
    virtual bool init(std::string name) = 0;
    virtual bool open(std::string name) = 0;
    virtual bool close(std::string name) = 0;
    virtual unsigned int read(std::string name, int index) = 0;
    virtual bool write(std::string name, int index, unsigned int value) = 0;;
    virtual bool write(std::string name, unsigned int value) = 0;
};