/* Copyright 2024 Code Love you */

#pragma once
#include "FileManager.h"
#include "LogManager.h"
#include "SSDWriter.h"
#include "SSDReader.h"
#include "SSDEraser.h"
#include "CommandBuffer.h"

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

    char cmd{ 0 };
    int index{ -1 };
    std::string write_value{ "" };
    int erase_size{ -1 };

    FileManager* file_manager;
    SSDWriter* ssd_writer;
    SSDReader* ssd_reader;
    SSDEraser* ssd_eraser;
    CommandBuffer* command_buffer;

    bool isValidCommand();
    bool isValidIndex();
    bool isValidArgCnt();
    bool isValidWriteInput();
    bool isValidEraseInput();

    std::string convertToUpperValue(std::string&);
    const std::string CLASS_NAME = "SDDManager";
};
