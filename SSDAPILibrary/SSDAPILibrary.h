#pragma once

#ifdef SSDAPILIBRARY_EXPORTS
#define SSDAPILIBRARY_API __declspec(dllexport)
#else
#define SSDAPILIBRARY_API __declspec(dllimport)
#endif

extern "C" SSDAPILIBRARY_API int SSDAPIWrite(const char* arg);
extern "C" SSDAPILIBRARY_API int SSDAPIRead(const char* arg, bool isPrint);
extern "C" SSDAPILIBRARY_API int SSDAPIFullWrite(const char* arg);
extern "C" SSDAPILIBRARY_API int SSDAPIFullRead(void);
extern "C" SSDAPILIBRARY_API int SSDAPIErase(const char* arg);
extern "C" SSDAPILIBRARY_API int SSDAPIEraseRange(const char* arg);
extern "C" SSDAPILIBRARY_API int SSDAPIFlush(void);