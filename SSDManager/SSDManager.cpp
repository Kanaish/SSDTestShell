/* Copyright 2024 Code Love you */

#include <string>
#include <vector>
#include <stdexcept>

class SSDManager {
 public:
    SSDManager(int argc, char** argv) {
        for (int i = 0; i < argc; i++) {
            parsed_command.push_back(argv[i]);
        }
    }

    bool isValidInput() {
        int argc = parsed_command.size();
        if (argc < 2) {
            return false;
        }

        std::string& cmd = parsed_command[1];
        if (cmd != "W" && cmd != "R") {
            return false;
        }

        if (argc < 3) {
            return false;
        }

        std::string& index = parsed_command[2];
        try {
            if (stoi(index) < 0 || stoi(index) > 99) {
                return false;
            }
        }
        catch (std::exception& e) {  // stoi() fail
            return false;
        }

        if (cmd == "W") {
            if (argc != 4) {
                return false;
            }

            std::string& value = parsed_command[3];
            if (value.length() != 10) {
                return false;
            }
            if (value.substr(0, 2) != "0x") {
                return false;
            }
            for (char& c : value.substr(2, 8)) {
                if (c < '0' || (c > '9' && c < 'A') || c > 'F') {
                    return false;
                }
            }
        }

        if (cmd == "R" && argc != 3) {
            return false;
        }

        return true;
    }

    std::vector<std::string> getParsedCommand() {
        return parsed_command;
    }

 private:
    std::vector<std::string> parsed_command;
};
