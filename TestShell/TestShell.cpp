/* Copyright 2024 Code Love you */

#include <iostream>

#include "TestShell.h"

void TestShell::run(void) {
}

bool TestShell::isValidCommand(const std::string& cmd) {
  return commandMap.find(cmd) != commandMap.end();
}

void TestShell::execute(std::string input_str) {
  size_t pos = input_str.find(' ');
  std::string cmd;
  std::string arg;

  if (pos == std::string::npos) {
    cmd = input_str;
    arg = "";
    return;
  }

  cmd = input_str.substr(0, pos);
  arg = input_str.substr(pos + 1);

  if (isValidCommand(cmd)) {
    commandMap.at(cmd)(arg);
    return;
  }

  std::cout << "Invalid command: " << cmd << std::endl;
}

bool TestShell::write(const std::string& arg) {
  return true;
}

bool TestShell::read(const std::string& arg) {
  return true;
}

void TestShell::exit(void) {
}

void TestShell::help(void) {
}

bool TestShell::fullWrite(const std::string& arg) {
  return true;
}

bool TestShell::fullRead(void) {
  return true;
}
