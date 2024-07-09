/* Copyright 2024 Code Love you */
#pragma once
#include<string>
#include "FileManager.h"

class SSDWriter {
 public:
    SSDWriter();
    void writer(int index, unsigned int value);
    std::fstream* getNandFileStream();
 private:
    FileManager file_mgr;
    std::fstream* nand_file_stream;
    const std::string FILENAME = "nand.txt";
};
