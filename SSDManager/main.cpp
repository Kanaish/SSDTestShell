/* Copyright 2024 Code Love you */

#include "SSDManager.h"

int main(int argc, char** argv) {
    SSDManager ssd(argc, argv);

    bool successFlag = ssd.executeCommand();
    if (successFlag == false) {
        return -1;
    }

    return 0;
}
