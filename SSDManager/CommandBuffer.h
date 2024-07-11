/* Copyright 2024 Code Love you */

#pragma once
#include <string>
#include <vector>

struct BufferData {
    char cmd;
    int index;
    std::string write_value;
    int erase_size;

    int getLastIndex() {
        return index + erase_size - 1;
    }
    bool operator<(const BufferData& compared) {
        if (index < compared.index) {
            return true;
        }
        if (index > compared.index) {
            return false;
        }
        if (index == compared.index) {
            return erase_size <= compared.erase_size;
        }
    }
};

class CommandBuffer {
 public:
    CommandBuffer();

    bool updateBuffer(BufferData);
    bool isFullBuffer();
    std::vector<BufferData> flushBuffer();
    std::string findMatchedWrite(int);
    bool flushBufferFile();

    const std::string BUFFER_FILE_NAME = "../../resources/buffer.txt";

 private:
    bool createBufferFile();
    bool readBufferFile();
    bool writeBufferFile();

    bool ignoreDupWrite(BufferData&, int, int);
    bool mergeLastErase(BufferData&);
    bool narrowEraseRange(BufferData&, int);
    bool narrowEraseRangeSeveralTimes(BufferData&);

    std::vector<BufferData> data;
    const char DELIMETER_STRING = ',';
    const char SPACE_STRING = ' ';
    const int BUFFER_MAX = 10;
    const std::string CLASS_NAME = "CommandBuffer";
};
