#include "SerialPort.h"

namespace SerialModule
{
    SerialPort::SerialPort()
        : m_isConnect(false) 
    {

    }

    SerialPort::SerialPort(const char* port, unsigned long baudRate)
        : m_isConnect(false)
    {
        Initialize(port, baudRate);
    }

    SerialPort::~SerialPort()
    {
        //Check if we are connected before trying to disconnect
        if (m_isConnect)
        {
            //We're no longer connected
            m_isConnect = false;
            //Close the serial handler
            CloseHandle(m_handler);
        }
    }

    void SerialPort::Initialize(const char* port, unsigned long baudRate)
    {
        //Open Serial Port
        m_handler = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (m_handler == INVALID_HANDLE_VALUE)
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
            if (!GetCommState(m_handler, &serialParameters))
            {
                //If impossible, show an error
                std::cout << "Failed to get current serial parameters" << std::endl;
            }
            else
            {
                //Define serial connection parameters for the arduino board
                serialParameters.BaudRate = baudRate;
                serialParameters.ByteSize = 8;
                serialParameters.StopBits = ONESTOPBIT;
                serialParameters.Parity = NOPARITY;

                //Set the parameters and check for their proper application
                if (!SetCommState(m_handler, &serialParameters))
                {
                    std::cout << "Could not set Serial Port parameters";
                }
                else
                {
                    //If everything went fine we're connected
                    m_isConnect = true;
                    //Flush any remaining characters in the buffers 
                    PurgeComm(m_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);

                }
            }
        }
    }

    std::vector<int> SerialPort::GetAvailablePorts()
    {
        char lpTargetPath[5000]; // buffer to store the path of the COM PORTS
        std::vector<int> portList;
        std::cout << "Active Ports" << std::endl;
        for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
        {
            std::string str = "COM" + std::to_string(i); // COM0 .. COM255
            DWORD name = QueryDosDeviceA(str.c_str(), lpTargetPath, 5000);

            
            if (name != 0) //QueryDosDevice returns zero if it didn't find an object
            {
                portList.push_back(i);
                std::cout << str << ": " << lpTargetPath << std::endl;
            }

        }
        return portList;
    }

    void SerialPort::ReceiveData(unsigned char& data, unsigned int byteSize)
    {
        ReadFile(m_handler, &data, byteSize, NULL, NULL); //Reads data from specified I/O device   
    }

    bool SerialPort::WriteData(const char* buffer) {
        DWORD bytesSend;
        if (!WriteFile(this->m_handler, (void*)buffer, 1, &bytesSend, 0)) {
            
            ClearCommError(this->m_handler, &this->errors, &this->status);
            std::cerr << "Error write" << std::endl;
            
            return false;
        }
        else
            return true;
    }

    bool SerialPort::CloseSerialPort()
    {
        if (m_isConnect) {
            m_isConnect = false;
            CloseHandle(m_handler);
            return true;
        }
        else
            return false;
    }

    bool SerialPort::IsConnected() const
    {
        return m_isConnect;
    }
}