#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <iostream>
#include <string>
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

#if defined (_WIN32) || defined (_WIN64)
#define WINDOWS 

#elif defined(unix) || defined(__unix) || defined(__unix__) || defined (__linux__)
#define LINUX
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

namespace SerialModule
{
    class SerialPort
    {
    public:
        void InitSpdLog();
        SerialPort();
        ~SerialPort();
        SerialPort(const char* port, unsigned long BaudRate);
        std::vector<int> GetAvailablePorts();  
        void Initialize(const char* port, unsigned long BaudRate);
        bool ReceiveData(uint8_t* buffer, uint8_t buffer_size);
        bool WriteData(const char* buffer);
        bool IsConnected() const;
        bool CloseSerialPort(const char* port);
    private:

    #ifdef WINDOWS
        HANDLE m_handler;
        bool m_isConnect;
        COMSTAT status;
        DWORD errors;
    #endif
    };

}

#endif // SERIALPORT.H