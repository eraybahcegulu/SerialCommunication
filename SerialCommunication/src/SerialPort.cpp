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

    bool SerialPort::IsConnected() const
    {
        return m_isConnect;
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
                spdlog::warn("{} is not active\n", port);

            }
            else
            {
                spdlog::error("Error creating port handle\n");
            }
        }

        else
        {
            spdlog::info("{} starting connection\n", port);
            //If connected we try to set the comm parameters
            DCB serialParameters; //Device Control Block

            //Try to get the current
            if (!GetCommState(m_handler, &serialParameters))
            {
                //If impossible, show an error
                spdlog::error("Failed to get current serial parameters\n");
            }
            else
            {
                //Define serial connection parameters for the arduino board
                serialParameters.BaudRate = baudRate;
                serialParameters.ByteSize = 8;
                serialParameters.StopBits = ONESTOPBIT;
                serialParameters.Parity = NOPARITY;
                serialParameters.fDtrControl = DTR_CONTROL_ENABLE;
                //Set the parameters and check for their proper application
                if (!SetCommState(m_handler, &serialParameters))
                {
                    spdlog::error("Could not set Serial Port parameters\n");
                }
                else
                {
                    //If everything went fine we're connected
                    m_isConnect = true;
                    //Flush any remaining characters in the buffers 
                    PurgeComm(m_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                    Sleep(2000);
                }
            }
        }
    }

    std::vector<int> SerialPort::GetAvailablePorts()
    {
        char lpTargetPath[5000]; // buffer to store the path of the COM PORTS
        std::vector<int> portList;
        spdlog::info("Active ports on the system");
        for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
        {
            std::string str = "COM" + std::to_string(i); // COM0 .. COM255
            DWORD name = QueryDosDeviceA(str.c_str(), lpTargetPath, 5000);


            if (name != 0) //QueryDosDevice returns zero if it didn't find an object
            {
                portList.push_back(i);
                spdlog::info("{} : {}", str , lpTargetPath);
            }

        }
        return portList;
    }

   

    bool SerialPort::ReceiveData(uint8_t* buffer, uint8_t buffer_size) {
        DWORD bytesRead = 0;
        unsigned int toRead = 0;

        ClearCommError(m_handler, &errors, &status);

        if (status.cbInQue > 0) {
            if (status.cbInQue > buffer_size) {
                toRead = buffer_size;
            }
            else toRead = status.cbInQue;

            if (ReadFile(m_handler, buffer, toRead, &bytesRead, NULL))
            return bytesRead;
        }

        return 0;
    }

    bool SerialPort::WriteData(const char* buffer) {
        DWORD bytesSend;
        if (!WriteFile(this->m_handler, (void*)buffer, 1, &bytesSend, 0)) {

            ClearCommError(this->m_handler, &this->errors, &this->status);
            spdlog::error("Data was not written\n");
            return false;
        }
        else
            spdlog::info("Data written successfully\n");
        return true;
    }

    void SerialPort::initSpdLog()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/logger.txt", 1048, 10, true);

        std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
        spdlog::init_thread_pool(8192, 1);
        auto async_logger = std::make_shared<spdlog::async_logger>("async logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        async_logger->flush_on(spdlog::level::trace);

        spdlog::set_default_logger(async_logger);
    }

    bool SerialPort::CloseSerialPort(const char* port)
    {
        if (m_isConnect) {
            m_isConnect = false;
            CloseHandle(m_handler);
            spdlog::info("{} connection closed" , port);
            return true;
        }
        else
            return false;
    }

   
}