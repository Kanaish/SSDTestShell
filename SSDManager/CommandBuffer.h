/* Copyright 2024 Code Love you */

#pragma once
#include <string>
#include <vector>

typedef struct BufferData {
    char cmd;
    int index;
    std::string write_value;
    int erase_size;
};

class CommandBuffer {
public:
    CommandBuffer(); // createBufferFile() 호출

    // 최적화 알고리즘 함수들 하나씩 다 해보고 -> vector에 업데이트
    // full이 아닐 때 writeBufferFile() 호출
    bool updateBuffer(BufferData);
    bool isFullBuffer();
    std::vector<BufferData> flushBuffer(); // data 전달 + 파일 비우기 (flushBufferFile() 호출)
    std::string findMatchedWrite(int index); // 있으면 value 값, 없으면 ""
    const std::string BUFFER_FILE_NAME = "../../resources/buffer.txt";

private:
    std::vector<BufferData> data;

    // 파일 뭔가 문제 생기면 (null을 리턴? exception이 떨어지는지?) 여기서 return false;
    bool createBufferFile(); // buffer.txt가 없으면 생성 (춘원님 코드 바로 넣기)
    bool readBufferFile(); // buffer.txt를 읽어서 data에 넣기 (delimeter: ,)
    bool writeBufferFile(); // data를 buffer.txt에 적기 (delimeter: ,)
    bool flushBufferFile(); // buffer.txt 파일 비우기

    // 최적화 알고리즘 함수들 넣기
};