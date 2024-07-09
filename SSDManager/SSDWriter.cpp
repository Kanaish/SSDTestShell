//    "Copyright [2024] <YD>
#include <fstream>
#include <iostream>
#include "SSDWriter.h"

SSDWriter::SSDWriter() {
    nand_file_stream = file_mgr.init(FILENAME);
}
void SSDWriter::writer(int index, unsigned int value) {
    file_mgr.write(nand_file_stream, index, value);
}
std::fstream* SSDWriter::getNandFileStream() {
    return nand_file_stream;
}