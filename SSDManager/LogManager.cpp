/* Copyright 2024 Code Love you */
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <cstring>
#include <locale>
#include <codecvt>
#include "LogManager.h"

LogManager::LogManager() {
}
void LogManager::logWrite(std::string mFunctionName, std::string className, std::string msg) {
    std::string logTitle(50, ' ');
    std::string buf = className + "::" + mFunctionName;
    logTitle.replace(0, buf.length(), buf);
    std::string logMessage = logGetCurrentTimeForLogging() + logTitle + msg + "\n";
    
    logPrint(logMessage);

    std::ofstream logFile(LOG_DIR + CURRENT_LOG, std::ios::out | std::ios::app);
    if (logFile.is_open()) {
        logFile.seekp(0, std::ios::end);
        logFile << logMessage;
        size_t pos = logFile.tellp();
        if (pos > LIMIT_LOG_SIZE) {
            logFile.close();
            std::string logNewFileName = LOG_DIR +"Until_" + logGetCurrentTimeForFileName() + ".log";
            //std::cout << pos << std::endl;
            //std::cout << CURRENT_LOG.c_str() << logNewFileName.c_str() << std::endl;
            //std::cout << "Log File Num : " << getOldLogFileNum() << std::endl;
            //std::cout << "Oldest Log File Name : " << getOldestLogFileName() << std::endl;
            if (std::rename((LOG_DIR + CURRENT_LOG).c_str(), logNewFileName.c_str()) != 0) {
                std::cerr << "Error renaming file" << std::endl;
                return;
            }
            if (getOldLogFileNum() == 2)
            {
                std::string oldestFileName = LOG_DIR + getOldestLogFileName();
                std::string changedOldestFileName = oldestFileName;

                size_t pos = oldestFileName.find(".log");
                changedOldestFileName.replace(pos, 4, ".zip");
                std::cout << "Oldest Log File Name : " << oldestFileName << std::endl;
                std::cout << "Changed Log File Name : " << changedOldestFileName << std::endl;
                if (std::rename(oldestFileName.c_str(), changedOldestFileName.c_str()) != 0) {
                    std::cerr << "Error renaming file" << std::endl;
                    return;
                }
            }
        }
    }
    else {

    }
    logFile.close();
}
void LogManager::logPrint(std::string msg) {
    std::cout << msg;
}
std::string LogManager::logGetCurrentTimeForLogging(void) {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
    std::string str_time(buffer);
    return  "[" + str_time + "] ";
}

std::string LogManager::logGetCurrentTimeForFileName(void) {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y_%m_%d_%H_%M_%S", tm);
    std::string str_time(buffer);
    return str_time;;
}

int LogManager::getOldLogFileNum(void) {
        const wchar_t* path = L"..\\log\\*_*_*_*_*_*.log";

        WIN32_FIND_DATA data;
        HANDLE hFind = FindFirstFile(path, &data);
        if (hFind == INVALID_HANDLE_VALUE) {
            std::cerr << "Could not open directory: " << path << '\n';
            return 1;
        }

        int count = 0;
        do {
            ++count;
        } while (FindNextFile(hFind, &data) != 0);

        FindClose(hFind);

        std::cout << "Number of .log files: " << count << '\n';

        return count;
}

std::string LogManager::getOldestLogFileName(void)
{
    WIN32_FIND_DATA data;
    HANDLE hFind;
    FILETIME oldestTime;
    SYSTEMTIME stUTC, stLocal;
    std::string oldestFile;
    const wchar_t* path = L"..\\log\\*_*_*_*_*_*.log";
    // 현재 디렉토리의 모든 .log 파일을 검색합니다.
    if ((hFind = FindFirstFile(path, &data)) != INVALID_HANDLE_VALUE) {
        oldestTime = data.ftLastWriteTime;
        oldestFile = WideStringToString(data.cFileName);

        while (FindNextFile(hFind, &data) != 0) {
            if (CompareFileTime(&data.ftLastWriteTime, &oldestTime) < 0) {
                oldestTime = data.ftLastWriteTime;
                oldestFile = WideStringToString(data.cFileName);
            }
        }

        FindClose(hFind);
    }

    // 가장 오래된 .log 파일의 이름을 출력합니다.
    if (!oldestFile.empty()) {
        // 파일 시간을 시스템 시간으로 변환합니다.
        FileTimeToSystemTime(&oldestTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        std::cout << "Oldest .log file: " << oldestFile;
        std::cout << ", Last modified: " << stLocal.wYear << "-" << stLocal.wMonth << "-" << stLocal.wDay << " " << stLocal.wHour << ":" << stLocal.wMinute << "\n";
    }
    else {
        std::cout << "No .log files found.\n";
    }
    return oldestFile;
}

std::string LogManager::WideStringToString(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}