#include "SerialPort.hpp"

SerialPort::SerialPort(const char* port, unsigned long BaudRate)
    : isConnect(false)
{
    Initialize(port, BaudRate);
}

//Bağlantı başlatma
void SerialPort::Initialize(const char* port, unsigned long BaudRate)
{
    // Serial Portu aç
    handler = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


    DCB serialParameters; //Cihaz Kontrol Bloğu
    //Seri port konfigürasyonu içeren yapı

    GetCommState(handler, &serialParameters); //COM parametrelerini al

    serialParameters.BaudRate = BaudRate;
    serialParameters.ByteSize = 8; /*8 bit data format*/
    serialParameters.StopBits = ONESTOPBIT;
    serialParameters.Parity = NOPARITY;

    SetCommState(handler, &serialParameters); //Değiştirilmiş COM parametrelerini gönder
}

/*Serial I/O*/
void SerialPort::receive(unsigned char &data, unsigned int byteSize)
{
    ReadFile(handler, &data, byteSize, NULL, NULL); //Belirtilen I/O aygıtından veriyi okur
}