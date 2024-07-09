/* Copyright 2024 Code Love you */

#include "SSDReader.h"

/*
fstream* open(string name);
fstream* init (string name)
bool write (fstream * fs, int index, uint32 value)
uint32 read (fstream * fs, int index)
bool write (fstream * fs, uint32 value)
bool close(fstream * fs)
*/

unsigned int SSDReader::read(int index) {
    unsigned int result = 0;

    result = readSSDValue(index);

    writeResultValue(result);

    return result;
}

void SSDReader::writeResultValue(unsigned int result) {
    std::fstream* f_result = m_fm->open(RESULT_NAME_PATH);
    if (f_result == NULL) {
        std::cout << "file open fail(" << RESULT_NAME_PATH << ")\n";
        // throw std::runtime_error("file open fail.");
    } else {
        m_fm->write(f_result, result);
        m_fm->close(f_result);
    }
}

unsigned int SSDReader::readSSDValue(int index) {
    unsigned int result = 0;

    std::fstream* f_ssd = m_fm->open(NAND_NAME_PATH);
    if (f_ssd == NULL) {
        std::cout << "file open fail(" << NAND_NAME_PATH << ")\n";
        // throw std::runtime_error("file open fail.");
    } else {
        result = m_fm->read(f_ssd, index);
        m_fm->close(f_ssd);
    }
    return result;
}
