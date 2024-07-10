#pragma once
/* Copyright 2024 Code Love you */

#include <string>
#include <unordered_map>
#include <functional>

class TestShell {
public:
    void run(void);
    void execute(const std::string inputStr);
    virtual int write(const std::string& arg);
    virtual int read(const std::string& arg);
    virtual int fullWrite(const std::string& arg);
    virtual int fullRead(const std::string& arg);
    virtual int testApp1(void);
    virtual int testApp2(void);

protected:
    virtual void exit(const std::string& arg);
    virtual void help(const std::string& arg);

private:
    bool isValidCommand(const std::string& cmd);
    bool isValidIndex(const std::string& str);
    bool isValidAddress(const std::string& str);
    bool isValidArgument(const std::string& arg);

    const std::unordered_map<std::string,
        std::function<void(const std::string&)>> commandMap = {
      {"write", [this](const std::string& arg) { this->write(arg); }},
      {"read", [this](const std::string& arg) { this->read(arg); }},
      {"exit", [this](const std::string& arg) { this->exit(arg); }},
      {"help", [this](const std::string& arg) { this->help(arg); }},
      {"fullwrite", [this](const std::string& arg) { this->fullWrite(arg); }},
      {"fullread", [this](const std::string& arg) { this->fullRead(arg); }},
      {"testapp1", [this](const std::string&) {this->testApp1(); }},
      {"testapp2", [this](const std::string&) {this->testApp2(); }},
    };
};
