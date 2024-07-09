/* Copyright 2024 Code Love you */

#include <string>
#include <vector>

class SSDManager {
 public:
    SSDManager(int argc, char** argv) {
        for (int i = 0; i < argc; i++) {
            parsed_command.push_back(argv[i]);
        }
    }

    std::vector<std::string> getParsedCommand() {
        return parsed_command;
    }

 private:
    std::vector<std::string> parsed_command;
};
