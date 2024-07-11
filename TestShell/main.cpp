/* Copyright 2024 Code Love you */

#include "TestShell.h"
#include "FileManager.h"

int main(int argc, char* argv[]) {
    FileManager file_manager;
    TestShell app{ &file_manager };

    app.run(argc, argv);

    return 0;
}
