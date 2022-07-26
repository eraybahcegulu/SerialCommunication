#include <windows.h>
#include <iostream>


namespace SerialModule
{
    class SerialPort
    {
    public:
        SerialPort();
        SerialPort(const char* port, unsigned long BaudRate);
        ~SerialPort();
        void Initialize(const char* port, unsigned long BaudRate);
        void ReceiveData(unsigned char& data, unsigned int byteSize);
        bool IsConnected() const;
        bool WriteData(const char* buffer);
        bool CloseSerialPort();
    private:
        HANDLE m_handler;
        bool m_isConnect;
    };

}
