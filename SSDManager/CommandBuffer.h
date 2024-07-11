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
    CommandBuffer(); // createBufferFile() ȣ��

    // ����ȭ �˰��� �Լ��� �ϳ��� �� �غ��� -> vector�� ������Ʈ
    // full�� �ƴ� �� writeBufferFile() ȣ��
    bool updateBuffer(BufferData);
    bool isFullBuffer();
    std::vector<BufferData> flushBuffer(); // data ���� + ���� ���� (flushBufferFile() ȣ��)
    std::string findMatchedWrite(int index); // ������ value ��, ������ ""

    const std::string BUFFER_FILE_NAME = "../../resources/buffer.txt";
    // const std::string BUFFER_FILE_NAME = "../resources/buffer.txt";

private:
    // ���� ���� ���� ����� (null�� ����? exception�� ����������?) ���⼭ return false;
    bool createBufferFile(); // buffer.txt�� ������ ���� (����� �ڵ� �ٷ� �ֱ�)
    bool readBufferFile(); // buffer.txt�� �о data�� �ֱ� (delimeter: ,)
    bool writeBufferFile(); // data�� buffer.txt�� ���� (delimeter: ,)
    bool flushBufferFile(); // buffer.txt ���� ����

    // ����ȭ �˰��� �Լ��� �ֱ�
    void ignoreDupWrite(BufferData& new_data);

    std::vector<BufferData> data;
    const char DELIMETER_STRING = ','; // "W 1 0x12345678,E 10 5,W 2 0x12345678,"
    const char SPACE_STRING = ' ';
    const int BUFFER_MAX = 10;
};