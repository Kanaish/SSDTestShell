/* Copyright 2024 Code Love you */

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <regex>
#include <stdexcept>

#include "TestShell.h"

void TestShell::run(void) {
}

bool TestShell::isValidCommand(const std::string& cmd) {
  return commandMap.find(cmd) != commandMap.end();
}

bool TestShell::isValidArgument(const std::string& arg) {
  std::istringstream iss(arg);
  std::string first_word, second_word, third_word;

  iss >> first_word >> second_word >> third_word;

  if (!third_word.empty()) {
    return false;
  }

  try {
    int number = std::stoi(first_word);
    if (number < 0 || number > 99) {
      return false;
    }
  }
  catch (std::invalid_argument const& e) {
    return false;
  }
  catch (std::out_of_range const& e) {
    return false;
  }

  if (second_word.size() != 10 || second_word.substr(0, 2) != "0x") {
    return false;
  }
  try {
    size_t pos;
    unsigned long value = std::stoul(second_word.substr(2), &pos, 16);
    if (pos != 8) {
      return false;
    }
  }
  catch (std::invalid_argument const& e) {
    return false;
  }
  catch (std::out_of_range const& e) {
    return false;
  }

  return true;
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

  throw std::invalid_argument("INVALID COMMAND");
}

int TestShell::write(const std::string& arg) {
  std::string cmd = "ssd.exe w ";

  if (isValidArgument(arg)) {
    cmd += arg;
    std::cout << cmd << std::endl;
    return system(cmd.c_str());
  }

  throw std::invalid_argument("INVALID COMMAND");
  return -1;
}

int TestShell::read(const std::string& arg) {
  return 0;
}

void TestShell::exit(void) {
}

void TestShell::help(void) {
}

int TestShell::fullWrite(const std::string& arg) {
  return 0;
}

int TestShell::fullRead(void) {
  return 0;
}
