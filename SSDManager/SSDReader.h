/* Copyright 2024 Code Love you */

#pragma once
#include <iostream>
// #include "FileManager.h"

#include <string>
const std::string RESULT_NAME_PATH = "result.txt";
const std::string NAND_NAME_PATH = "nand.txt";

#define interface struct

#if 0
interface FileManagerInterface {
    virtual std::fstream* open(std::string name) = 0;
    virtual std::fstream* init(std::string name) = 0;
    virtual bool write(std::fstream* fs, int index, unsigned int value) = 0;
    virtual unsigned int read(std::fstream* fs, int index) = 0;
    virtual bool write(std::fstream* fs, unsigned int value) = 0;
    virtual bool close(std::fstream* fs) = 0;
};

class FileManager : public FileManagerInterface {
 public:
    std::fstream* open(std::string name) { return NULL; }
    std::fstream* init(std::string name) { return NULL; }
    bool write(std::fstream* fs, int index, unsigned int value) { return true; }
    unsigned int read(std::fstream* fs, int index) { return 0; }
    bool write(std::fstream* fs, unsigned int value) { return true; }
    bool close(std::fstream* fs) { return true; }
};
#else
class FileManager {
 public:
    virtual std::fstream* open(std::string name) { return NULL; }
    virtual std::fstream* init(std::string name) { return NULL; }
    virtual bool write(std::fstream* fs, int index, unsigned int value) { return true; }
    virtual unsigned int read(std::fstream* fs, int index) { return 0; }
    virtual bool write(std::fstream* fs, unsigned int value) { return true; }
    virtual bool close(std::fstream* fs) { return true; }
};
#endif

class SSDReader {
 public:
    SSDReader() {
        m_fm = &fm;
        m_fm->init(RESULT_NAME_PATH);
    }
    SSDReader(FileManager* fm) : m_fm(fm) {
        fm->init(RESULT_NAME_PATH);
    }
    unsigned int read(int index);

 private:
    void writeResultValue(unsigned int result);
    unsigned int readSSDValue(int index);

    FileManager fm;
    FileManager* m_fm;
};
