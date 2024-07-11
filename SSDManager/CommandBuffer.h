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
    bool operator<(BufferData& compared) {
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
    CommandBuffer(); // createBufferFile() 호출

    // 최적화 알고리즘 함수들 하나씩 다 해보고 -> vector에 업데이트
    // full이 아닐 때 writeBufferFile() 호출
    bool updateBuffer(BufferData);
    bool isFullBuffer();
    std::vector<BufferData> flushBuffer(); // data 전달 + 파일 비우기 (flushBufferFile() 호출)
    std::string findMatchedWrite(int); // 있으면 value 값, 없으면 ""
    bool flushBufferFile(); // buffer.txt 파일 비우기

    const std::string BUFFER_FILE_NAME = "../../resources/buffer.txt";
    // const std::string BUFFER_FILE_NAME = "../resources/buffer.txt";

private:
    // 파일 뭔가 문제 생기면 (null을 리턴? exception이 떨어지는지?) 여기서 return false;
    bool createBufferFile(); // buffer.txt가 없으면 생성 (춘원님 코드 바로 넣기)
    bool readBufferFile(); // buffer.txt를 읽어서 data에 넣기 (delimeter: ,)
    bool writeBufferFile(); // data를 buffer.txt에 적기 (delimeter: ,)
    

    // 최적화 알고리즘 함수들 넣기
    bool ignoreDupWrite(BufferData&, int, int);
    bool mergeLastErase(BufferData&);
    bool narrowEraseRange(BufferData&, int);
    bool narrowEraseRangeSeveralTimes(BufferData& new_data);

    std::vector<BufferData> data;
    const char DELIMETER_STRING = ','; // "W 1 0x12345678,E 10 5,W 2 0x12345678,"
    const char SPACE_STRING = ' ';
    const int BUFFER_MAX = 10;
};