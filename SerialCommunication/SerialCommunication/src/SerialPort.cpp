#include "SerialPort.h"

SerialModule::SerialPort::SerialPort(const char* port, unsigned long BaudRate)
    : isConnect(false)
{
    Initialize(port, BaudRate);
}

//initialize serial port connection
void SerialModule::SerialPort::Initialize(const char* port, unsigned long BaudRate)
{
    //Open Serial Port
    handler = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


    DCB serialParameters; //Device Control Block
    //Structure with serial port configuration

    GetCommState(handler, &serialParameters); //get COM parameters

    serialParameters.BaudRate = BaudRate;
    serialParameters.ByteSize = 8; /*8 bit data format*/
    serialParameters.StopBits = ONESTOPBIT;
    serialParameters.Parity = NOPARITY;

    SetCommState(handler, &serialParameters); //Send modified COM parameters
    
    isConnect = true;
    PurgeComm(handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
    //Discards all characters from the output or input buffer of a specified communications resource
    //PURGE_RXCLEAR -- Clears the input buffer (if the device driver has one).
    //PURGE_TXCLEAR -- Clears the output buffer (if the device driver has one).
}

/*Serial I/O*/
void SerialModule::SerialPort::receive(unsigned char &data, unsigned int byteSize)
{
    ReadFile(handler, &data, byteSize, NULL, NULL); //Reads data from specified I/O device
}