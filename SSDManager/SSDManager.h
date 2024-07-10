/* Copyright 2024 Code Love you */

#pragma once
#include <string>
#include <vector>
#include "FileManager.h"
#include "SSDWriter.h"
#include "SSDReader.h"

class SSDManager {
 public:
    SSDManager(int argc, char** argv);
    ~SSDManager();

    bool isValidInput();
    bool executeCommand();
    std::vector<std::string> getParsedCommand();

    const std::string NAND_FILE = "../../resources/nand.txt";
    const std::string RESULT_FILE = "../../resources/result.txt";

 private:
    std::vector<std::string> parsed_input;

    FileManager* file_manager;
    SSDWriter* ssd_writer;
    SSDReader* ssd_reader;

    bool isValidCommand(int argc);
    bool isValidIndex(int argc);
    bool isValidReadInput(int argc);
    bool isValidWriteInput(int argc);

    int convertIndexInt();
    const std::string CLASS_NAME = "SSDManager";
};
