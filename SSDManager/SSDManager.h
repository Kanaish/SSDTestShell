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
    std::vector<std::string> getParsedInput();

    const std::string NAND_FILE = "../../resources/nand.txt";
    const std::string RESULT_FILE = "../../resources/result.txt";

 private:
    std::vector<std::string> parsed_input;
    int parsed_input_arg_cnt;

    const char INIT_CMDCODE = 'X';
    const int INIT_INDEX = -1;
    const std::string INIT_VALUE = "";

    char cmd{ INIT_CMDCODE };
    int index{ INIT_INDEX };
    std::string value{ INIT_VALUE };

    FileManager* file_manager;
    SSDWriter* ssd_writer;
    SSDReader* ssd_reader;

    bool isValidCommand();
    bool isValidIndex();
    bool isValidArgCnt();
    bool isValidWriteInput();
};
