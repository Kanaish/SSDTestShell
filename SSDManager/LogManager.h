/* Copyright 2024 Code Love you */
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
class LogManager
{
public:
    LogManager();
    void logWrite(std::string mFunctionName, std::string className, std::string msg);
    void logPrint(std::string msg);
private:
    std::string logGetCurrentTimeForLogging(void);
    std::string logGetCurrentTimeForFileName(void);
    int getOldLogFileNum(void);
    std::string getOldestLogFileName(void);
    std::string WideStringToString(const std::wstring& wstr);
    const std::string LOG_DIR = "..\\log\\";
    const std::string CURRENT_LOG = "lastest.log";
    const int LIMIT_LOG_SIZE = 10*1000;
};