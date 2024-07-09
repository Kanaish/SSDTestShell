//    "Copyright [2024] <YD>
#include <fstream>
#include <iostream>
#include "FileManager.h"

class SSDWriter {
 public:
    SSDWriter() {
        nand_file_stream = file_mgr.init(FILENAME);
    }
    void writer(int index, unsigned int value) {
        file_mgr.write(nand_file_stream, index, value);
    }
    std::fstream * getNandFileStream() {
        return nand_file_stream;
    }
 private:
    FileManager file_mgr;
    std::fstream * nand_file_stream;
    const std::string FILENAME = "nand.txt";
};
