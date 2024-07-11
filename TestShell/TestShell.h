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
    void execute(const std::string inputStr);
    virtual int write(const std::string& arg);
    virtual int read(const std::string& arg);
    virtual int fullWrite(const std::string& arg);
    virtual int fullRead();
    virtual int testApp1(void);
    virtual int testApp2(void);
    void transStringtoIntInt(const std::string& arg, int& left_arg, int& right_arg);
    int erase(const std::string& arg);
    int erase_range(const std::string& arg);

    FileManagerInterface* file_manager;

 protected:
    virtual void exit();
    virtual void help();

 private:
    bool isValidCommand(const std::string& cmd);
    bool isValidIndex(const std::string& str);
    bool isValidIndex2(const std::string& str);
    bool isValidAddress(const std::string& str);
    bool isValidArgument(const std::string& arg);
    int doErase(int start_lba, int size);

    const std::unordered_map<std::string,
        std::function<void(const std::string&)>> commandMap = {
      {"write", [this](const std::string& arg) { this->write(arg); }},
      {"read", [this](const std::string& arg) { this->read(arg); }},
      {"exit", [this](const std::string&) { this->exit(); }},
      {"help", [this](const std::string&) { this->help(); }},
      {"fullwrite", [this](const std::string& arg) { this->fullWrite(arg); }},
      {"fullread", [this](const std::string& arg) { this->fullRead(); }},
      {"testapp1", [this](const std::string&) {this->testApp1(); }},
      {"testapp2", [this](const std::string&) {this->testApp2(); }},
      {"erase", [this](const std::string& arg) {this->erase(arg); }},
      {"erase_range", [this](const std::string& arg) {this->erase_range(arg); }},
    };
};
