#include <windows.h>
#include <iostream>

class SerialPort
{
public:
    //Constructors
    SerialPort(const char* port, unsigned long BaudRate); //seri port bağlantı noktasını kuran yapıcı

    //Initialization
    void Initialize(const char* port, unsigned long BaudRate); //bağlantıyı başlat.

    //Serial I/O
    void receive(unsigned char &data, unsigned int byteSize); //veriyi alma

private:
    HANDLE handler;
    bool isConnect;
};
