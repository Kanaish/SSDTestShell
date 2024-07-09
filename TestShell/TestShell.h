#pragma once
/* Copyright 2024 Code Love you */

#include <string>
#include <unordered_map>
#include <functional>

class TestShell {
 public:
  void run(void);
  void execute(const std::string inputStr);

 protected:
  virtual bool write(const std::string& arg);
  virtual bool read(const std::string& arg);
  virtual void exit(void);
  virtual void help(void);
  virtual bool fullWrite(const std::string& arg);
  virtual bool fullRead(void);

 private:
  bool isValidCommand(const std::string& cmd);

  const std::unordered_map<std::string,
      std::function<void(const std::string&)>> commandMap = {
    {"write", [this](const std::string& arg) { this->write(arg); }},
    {"read", [this](const std::string& arg) { this->read(arg); }},
    {"exit", [this](const std::string&) { this->exit(); }},
    {"help", [this](const std::string&) { this->help(); }},
    {"fullwrite", [this](const std::string& arg) { this->fullWrite(arg); }},
    {"fullread", [this](const std::string&) { this->fullRead(); }}
  };
};
