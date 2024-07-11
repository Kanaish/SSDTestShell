/* Copyright 2024 Code Love you */

#include "pch.h"
#include "FileManager.h"

FileManager::FileManager() {
}

std::string FileManager::read(std::string name) {
    std::fstream resultFile(name, std::ios::in | std::ios::out);
    std::string ret;
    if (resultFile.is_open())
    {
        /* read result and store to the buffer */
        std::stringstream buffer;
        buffer << resultFile.rdbuf();
        ret = buffer.str();
    }
    else {
        throw std::invalid_argument("File is not opened");
    }
    resultFile.close();
    return ret;
}

std::string FileManager::read(std::string name, int index) {
    std::fstream nandFile(name, std::ios::in | std::ios::out);
    std::string ret;
    if (nandFile.is_open())
    {
        /* read nand and store to the buffer */
        std::stringstream buffer;
        buffer << nandFile.rdbuf();
        /* Get logic block address token */
        std::string tokenLba = generateToken(index);
        /* Find token in nand */
        size_t pos = buffer.str().find(tokenLba);
        if (pos != std::string::npos) {
            /* If token is found, read LBA */
            size_t posValue = buffer.str().find(" ", pos);
            ret = buffer.str().substr(posValue + 1, VALUE_LEN);
        }
        else {
            /* If not, return empty value */
            ret = EMPTY;
        }
    }
    else {
        throw std::invalid_argument("File is not opened");
    }
    nandFile.close();
    return ret;
}

bool FileManager::write(std::string name, int index, std::string value) {

    std::fstream nandFile(name, std::ios::in | std::ios::out);

    if (nandFile.is_open()) {
        nandFile.seekp(0, std::ios::beg);

        std::stringstream buffer;
        buffer << nandFile.rdbuf();
        /* Move file pointer to the beginning */
        nandFile.seekp(0, std::ios::beg);
        /* Find token in nand */
        size_t pos = buffer.str().find(generateToken(index));
        if (pos != std::string::npos) {
            /* If token is found, replace LBA with given value */
            nandFile.seekp(pos, std::ios::beg);
            nandFile << generateMemoryBlock(generateToken(index), value);
        }
        else {
            /* If not, replace LBA with given value */
            nandFile.seekp(0, std::ios::end);
            nandFile << generateMemoryBlock(generateToken(index), value);
        }
    }
    else {
        throw std::invalid_argument("File is not opened");
        return false;
    }
    nandFile.close();
    return true;
}

bool FileManager::write(std::string name, std::string value) {
    std::fstream resultFile(name, std::ios::in | std::ios::out);
    if (resultFile.is_open()) {
        resultFile.seekp(0, std::ios::beg);
        resultFile << value;
    }
    else {
        throw std::invalid_argument("File is not opened");
        return false;
    }
    resultFile.close();
    return true;
}

std::string FileManager::generateToken(int index)
{
    return std::string("LBA" + std::to_string(index));
}

std::string FileManager::generateMemoryBlock(std::string token, std::string value)
{
    return token + " " + value + " ";
}