#include "SerialPort.h"


/*Constructors*/
SerialModule::SerialPort::SerialPort()
    : isConnect(false) {}

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

    if (handler == INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {

            //Print Error if neccessary
            std::cout << port << " is not active" << std::endl;

        }
        else
        {
            std::cout << "Error" << std::endl;
        }
    }

    

    else
    {
        std::cout << port << " is active" << std::endl;
        //If connected we try to set the comm parameters
        DCB serialParameters; //Device Control Block

        //Try to get the current
        if (!GetCommState(handler, &serialParameters))
        {
            //If impossible, show an error
            std::cout << "Failed to get current serial parameters" << std::endl;
        }
        else
        {
            //Define serial connection parameters for the arduino board
            serialParameters.BaudRate = BaudRate;
            serialParameters.ByteSize = 8;
            serialParameters.StopBits = ONESTOPBIT;
            serialParameters.Parity = NOPARITY;

      

            //Set the parameters and check for their proper application
            if (!SetCommState(handler, &serialParameters))
            {
                std::cout << "Could not set Serial Port parameters";
            }
            else
            {
                //If everything went fine we're connected
                isConnect = true;
                //Flush any remaining characters in the buffers 
                PurgeComm(handler, PURGE_RXCLEAR | PURGE_TXCLEAR);

            }
        }
    }
}

SerialModule::SerialPort::~SerialPort()
{
    //Check if we are connected before trying to disconnect
    if (isConnect)
    {
        //We're no longer connected
        isConnect = false;
        //Close the serial handler
        CloseHandle(handler);
    }
}

/*Serial I/O*/
void SerialModule::SerialPort::receive(unsigned char& data, unsigned int byteSize)
{
    ReadFile(handler, &data, byteSize, NULL, NULL); //Reads data from specified I/O device   
}


bool SerialModule::SerialPort::isConnected()
{
    return isConnect;
}