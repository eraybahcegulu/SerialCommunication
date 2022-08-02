#include <windows.h>
#include <iostream>

#include <string>
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

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
        HANDLE m_handler;
        bool m_isConnect;
        COMSTAT status;
        DWORD errors;
        
    };

}
