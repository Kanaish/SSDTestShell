/* Copyright 2024 Code Love you */
#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

#define LOG_STORE(msg) do {LogManager::getLogManagerInstance().logPrint\
                                     (CLASS_NAME, __func__, msg);}while(0)
#define LOG_PRINT(msg) do {LogManager::getLogManagerInstance().logWrite\
                                     (CLASS_NAME, __func__, msg);}while(0)
#define LOG(msg) do {LOG_PRINT(msg); LOG_STORE(msg);}while(0)

class LogManager {
 public:
    static LogManager& getLogManagerInstance(void);
    void logWrite(std::string className, std::string mFunctionName,
                                                    std::string msg);
    void logPrint(std::string className, std::string mFunctionName,
                                                    std::string msg);

 private:
    LogManager();

    std::string logGetCurrentTimeForLogging(void);
    std::string logGetCurrentTimeForFileName(void);
    int getOldLogFileNum(void);
    std::string getOldestLogFileName(void);
    std::string WideStringToString(const std::wstring& wstr);

    const std::string LOG_DIR = "..\\..\\log\\";
    const std::string CURRENT_LOG = "lastest.log";
    const wchar_t* PATH = L"../../\\log\\*_*_*_*_*_*.log";;
    const int LIMIT_LOG_SIZE = 10*1000;
    const int LOG_TITLE_LIMIT = 50;

    LogManager& operator=(const LogManager& other) = delete;
    LogManager(const LogManager& other) = delete;
};
