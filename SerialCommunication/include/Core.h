#pragma once
#if defined (_WIN32) || defined (_WIN64)
#define WINDOWS 

#elif defined(unix) || defined(__unix) || defined(__unix__) || defined (__linux__)
#define LINUX
#endif