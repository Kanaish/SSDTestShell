/* Copyright 2024 Code Love you */

#include "SSDManager.h"
#include "LogManager.h"

int main(int argc, char** argv) {
    LogManager& logger = LogManager::getLogManagerInstance();
    SSDManager ssd(argc, argv, &logger);

    bool success_flag = ssd.executeCommand();
    if (success_flag == false) {
        return -1;
    }

    return 0;
}
