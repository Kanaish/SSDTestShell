/* Copyright 2024 Code Love you */
#pragma once
#include <string>

class FileManagerInterface {
public:
    virtual bool init(std::string name) = 0;
    virtual bool open(std::string name) = 0;
    virtual bool close(std::string name) = 0;
    virtual std::string read(std::string name, int index) = 0;
    virtual bool write(std::string name, int index, std::string value) = 0;;
    virtual bool write(std::string name, std::string value) = 0;
};