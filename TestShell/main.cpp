/* Copyright 2024 Code Love you */

#include "TestShell.h"
#include "FileManager.h"

int main() {
    FileManager file_manager;
    TestShell app{ &file_manager };

    app.run();

    return 0;
}
