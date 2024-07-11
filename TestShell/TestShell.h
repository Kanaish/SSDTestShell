#pragma once
/* Copyright 2024 Code Love you */

#include <string>
#include <unordered_map>
#include <functional>
#include "FileManagerInterface.h"

class TestShell {
 public:
    explicit TestShell(FileManagerInterface* file_manager)
        : file_manager(file_manager) {}
    void run(void);
    int execute(const std::string inputStr, bool fromScenarioFile = false);
    virtual int write(const std::string& arg);
    virtual int read(const std::string& arg, bool isPrint = true);
    virtual int fullWrite(const std::string& arg);
    virtual int fullRead();
    virtual int testApp1(void);
    virtual int testApp2(void);
    int erase(const std::string& arg);
    int erase_range(const std::string& arg);
    int flush(void);

    FileManagerInterface* file_manager;

    static const int SYSTEM_ERROR = -1;
    static const int INVALID_ARGUMENT = -2;
    static const int INVALID_COMMAND = -3;
    static const int TEST_FAIL = -4;

 protected:
    virtual int exit();
    virtual int help();

 private:
    bool isValidCommand(const std::string& cmd);
    int doErase(int start_lba, int size);
    void runScenarioFile(const std::string& filename);

    const std::unordered_map<std::string,
        std::function<int(const std::string&)>> commandMap = {
      {"write", [this](const std::string& arg) { return this->write(arg); }},
      {"read", [this](const std::string& arg) { return this->read(arg); }},
      {"exit", [this](const std::string&) { return this->exit(); return 0; }},
      {"help", [this](const std::string&) { return this->help(); return 0; }},
      {"fullwrite", [this](const std::string& arg)
            { return this->fullWrite(arg); }},
      {"fullread", [this](const std::string& arg) { return this->fullRead(); }},
      {"testapp1", [this](const std::string&) { return this->testApp1(); }},
      {"testapp2", [this](const std::string&) { return this->testApp2(); }},
      {"erase", [this](const std::string& arg) { return this->erase(arg); }},
      {"erase_range", [this](const std::string& arg)
            { return this->erase_range(arg); }},
      {"flush", [this](const std::string&) { return this->flush(); }},
    };

    const std::string TEST_SCENARIO_NAME = "run_list";
    const std::string HELP_FILE_PATH = "../../resources/help.txt";
    const std::string RESULT_FILE_PATH = "../../resources/result.txt";
    const std::string RESOURCE_PATH = "../../resources/";
};
