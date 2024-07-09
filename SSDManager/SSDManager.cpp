/* Copyright 2024 Code Love you */

#include <string>
#include <vector>
#include <stdexcept>

class SSDManager {
 public:
    SSDManager(int argc, char** argv) {
        for (int i = 0; i < argc; i++) {
            parsed_input.push_back(argv[i]);
        }
    }

    bool isValidInput() {
        int argc = parsed_input.size();

        if (isValidCommand(argc) == false) {
            return false;
        }

        if (isValidIndex(argc) == false) {
            return false;
        }

        if (isValidWriteInput(argc) == false) {
            return false;
        }

        if (isValidReadInput(argc) == false) {
            return false;
        }

        return true;
    }

    std::vector<std::string> getParsedCommand() {
        return parsed_input;
    }

 private:
    std::vector<std::string> parsed_input;

    bool isValidCommand(int argc) {
        if (argc < 2) {
            return false;
        }

        std::string cmd = parsed_input[1];
        if (cmd != "W" && cmd != "R") {
            return false;
        }

        return true;
    }

    bool isValidIndex(int argc) {
        if (argc < 3) {
            return false;
        }

        std::string& index = parsed_input[2];
        try {
            if (stoi(index) < 0 || stoi(index) > 99) {
                return false;
            }
        }
        catch (std::exception& e) {  // stoi() fail
            return false;
        }

        return true;
    }

    bool isValidReadInput(int argc) {
        std::string cmd = parsed_input[1];

        if (cmd == "R" && argc != 3) {
            return false;
        }

        return true;
    }

    bool isValidWriteInput(int argc) {
        std::string cmd = parsed_input[1];

        if (cmd == "W") {
            if (argc != 4) {
                return false;
            }

            std::string& value = parsed_input[3];
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

        return true;
    }
};
