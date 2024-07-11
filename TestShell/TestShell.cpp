/* Copyright 2024 Code Love you */

#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include "TestShell.h"
#include "SSDAPILibrary.h"
#include "LogManager.h"

void TestShell::run(void) {
    std::string input_str;
    LOG("Test Shell Run");
    while (1) {
        std::getline(std::cin, input_str);
        if (input_str.empty()) continue;
        if (input_str.substr(0, 8) == TEST_SCENARIO_NAME) {
            try {
                runScenarioFile(input_str);
            }
            catch (const std::exception& e) {
                std::cerr << "Error running scenario file: " << e.what() << std::endl;
            }
        }
        else {
            try {
                this->execute(input_str);
            }
            catch (std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

bool TestShell::isValidCommand(const std::string& cmd) {
    return commandMap.find(cmd) != commandMap.end();
}

int TestShell::execute(std::string input_str, bool fromScenarioFile) {
    LOG("Test Execute");
    size_t pos = input_str.find(' ');
    std::string cmd = (pos == std::string::npos) ?
        input_str : input_str.substr(0, pos);
    std::string arg = (pos == std::string::npos) ?
        "" : input_str.substr(pos + 1);

    if (!isValidCommand(cmd)) {
        throw std::invalid_argument("INVALID COMMAND");
    }

    if (cmd == "fullread" || cmd == "exit" || cmd == "help"
        || cmd == "testapp1" || cmd == "testapp2" || cmd =="flush") {
        if (!arg.empty()) {
            throw std::invalid_argument("INVALID COMMAND");
        }
    }

    int ret = commandMap.at(cmd)(arg);
    
    if (ret != 0) {
        if (fromScenarioFile) {
            return -1;
        }
        switch (ret) {
        case (SYSTEM_ERROR):
            throw std::invalid_argument("SYSTEM_ERROR");
        case (INVALID_ARGUMENT):
            throw std::invalid_argument("INVALID ARGUMENT");
        case (INVALID_COMMAND) :
            throw std::invalid_argument("INVALID COMMAND");
        case (TEST_FAIL) : 
            throw std::invalid_argument("TEST FAIL");
        default:
            throw std::invalid_argument("error");
        }
    }
    return ret;
}

int TestShell::write(const std::string& arg) {
    return SSDAPIWrite(arg.c_str());
}

int TestShell::read(const std::string& arg, bool isPrint) {
    return SSDAPIRead(arg.c_str(), isPrint);
}

int TestShell::exit() {
    std::exit(0);
    return 0;
}

int TestShell::help() {
    std::cout << file_manager->read("../../resources/help.txt") << std::endl;
    return 0;
}

int TestShell::fullWrite(const std::string& arg) {
    return SSDAPIFullWrite(arg.c_str());
}

int TestShell::fullRead() {
    return SSDAPIFullRead();
}

int TestShell::testApp1(void) {
    std::string write_value = "0xAAAABBBB";
    int ret = SSDAPIFullWrite(write_value.c_str());
    if (ret != 0) {
        return ret;
    }

    for (int lba = 0; lba < 100; lba++) {
        ret = SSDAPIRead(std::to_string(lba).c_str(), false);
        if (ret != 0) {
            return ret;
        }

        std::string line = file_manager->read("../../resources/result.txt");
        if (line != write_value) {
            ret = TEST_FAIL;
            break;
        }
    }
    return ret;
}

int TestShell::testApp2(void) {
    std::string write_value = "0xAAAABBBB";
    int ret = 0;
    for (int i = 0; i < 30; ++i) {
        for (int lba = 0; lba <= 5; ++lba) {
            std::string arg = std::to_string(lba) + " " + write_value;
            ret = SSDAPIWrite(arg.c_str());
            if (ret != 0) {
                return ret;
            }
        }
    }

    write_value = "0x12345678";
    for (int lba = 0; lba <= 5; ++lba) {
        std::string arg = std::to_string(lba) + " " + write_value;
        ret = SSDAPIWrite(arg.c_str());
        if (ret != 0) {
            return ret;
        }
    }

    for (int lba = 0; lba <= 5; ++lba) {
        SSDAPIRead(std::to_string(lba).c_str(), false);
        if (ret != 0) {
            return ret;
        }
        std::string line = file_manager->read("../../resources/result.txt");
        if (line != write_value) {
            ret = TEST_FAIL;
            break;
        }
    }

    return ret;
}

int TestShell::erase(const std::string& arg) {
    return SSDAPIErase(arg.c_str());
}

int TestShell::erase_range(const std::string& arg) {
    return SSDAPIEraseRange(arg.c_str());
}

void TestShell::runScenarioFile(const std::string& filename) {
    try {
        std::string fullPath = "../../resources/" + filename;
        std::string file_content = file_manager->read(fullPath);
        if (file_content.empty()) {
            throw std::runtime_error("File is not opened or is empty");
        }

        std::istringstream infile(file_content);
        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) continue;

            std::cout << line << " --- Run...";
            int result = execute(line, true);
            if (result != 0) {
                std::cout << "FAIL!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::exit(1);
            }
            else std::cout << "Pass" << std::endl;
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error reading file: " << filename << " - " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error executing command from file: " << filename << " - " << e.what() << std::endl;
    }
}

int TestShell::flush(void) {
    int ret = SSDAPIFlush();

    return ret;
}
