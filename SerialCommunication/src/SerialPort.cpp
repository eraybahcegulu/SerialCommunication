#include "SerialPort.h"

namespace SerialModule
{
#ifdef WINDOWS

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

    void SerialPort::InitSpdLog()
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

#endif

#ifdef LINUX
    char SerialPort::OpenPortLinux(char* port, int baud, char bits, parity parity, char stopbit)
    {
        char tmp[BUFFER_SIZE];

        // Convert to string
        sprintf(tmp, "%s", port);

        m_fd = open(tmp, O_RDWR | O_NOCTTY | O_NONBLOCK);

        // Check opening status 
        if (m_fd < 0)
        {
            spdlog::error("Error opening {} port\n", tmp);
            return 0;
        }

        // Get terminal parameters
        tcgetattr(m_fd, &m_newtio);
        tcgetattr(m_fd, &m_oldtio);

        // Flushes data received but not read		
        ioctl(m_fd, TCIFLUSH);

        // Set baud rate (in and out)
        switch (baud)
        {
        case 9600: cfsetspeed(&m_newtio, B9600); break;
        case 19200: cfsetspeed(&m_newtio, B19200); break;
        case 38400: cfsetspeed(&m_newtio, B38400); break;
        case 57600: cfsetspeed(&m_newtio, B57600); break;
        case 115200: cfsetspeed(&m_newtio, B115200); break;
        default: cfsetspeed(&m_newtio, B9600); break;
        }

        // Set byte size
        m_newtio.c_cflag &= ~CSIZE;

        switch (bits)
        {
        case 5: m_newtio.c_cflag |= CS5; break;
        case 6: m_newtio.c_cflag |= CS6; break;
        case 7: m_newtio.c_cflag |= CS7; break;
        case 8: m_newtio.c_cflag |= CS8; break;
        default: m_newtio.c_cflag |= CS8; break;
        }

        // Set parity
        switch (parity)
        {
        case NO:
            m_newtio.c_cflag &= ~PARENB;	// Disable parity
            break;

        case EVEN:
            m_newtio.c_cflag |= PARENB;		// Enable parity
            m_newtio.c_cflag &= ~PARODD;	// Disable odd parity
            break;

        case ODD:
            m_newtio.c_cflag |= PARENB;		// Enable parity
            m_newtio.c_cflag |= PARODD;		// Enable odd parity
            break;

        default:
            m_newtio.c_cflag &= ~PARENB;	// Disable parity
        }

        // Set stop bit
        switch (stopbit)
        {
        case 1: m_newtio.c_cflag &= ~CSTOPB; break;	// Disable 2 stop bits
        case 2: m_newtio.c_cflag |= CSTOPB; break;	// Enable 2 stop bits
        default: m_newtio.c_cflag &= ~CSTOPB;
        }

        // Enable receiver (CREAD) and ignore modem control lines (CLOCAL)
        m_newtio.c_cflag |= (CREAD | CLOCAL);

        // Disable, canonical mode (ICANON = 0), echo input character (ECHO) and signal generation (ISIG)
        m_newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

        // Disable input parity checking (INPCK)
        m_newtio.c_iflag &= ~INPCK;

        // Disable XON/XOFF flow control on output and input (IXON/IXOFF), framing and parity errors (IGNPAR), and disable CR to NL translation
        m_newtio.c_iflag &= ~(IXON | IXOFF | IXANY | IGNPAR | ICRNL);

        // Disable implementation-defined output processing (OPOST)
        m_newtio.c_oflag &= ~OPOST;

        // Set terminal parameters
        tcsetattr(m_fd, TCSAFLUSH, &m_newtio);

        // Display settings
        spdlog::info("{} | BaudRate: {} | Bits: {} | Parity: {} | StopBits: {}\n", tmp, baud, bits, parity, stopbit);
        return 1;
    }

    char SerialPort::WriteData(char* buffer, int length)
    {
        ssize_t r;
        const uint8_t* pos = (const uint8_t*)buffer;

        // Send data
        while (length > 0)
        {
            r = write(m_fd, pos, length);

            if (r < 1)
            {
                return 0;
            }

            length -= r;
            pos += r;
        }

        return 1;
    }

    int SerialPort::ReadData(char* buffer)
    {
        ssize_t r = 1;
        int length = 0;

        // Set timeout between 2 bytes (20ms)
        timeout timeout(TIME_OUT);

        //memset(buffer, 0x00, BUFFER_SIZE);

        while ((r > 0) || timeout.end())
        {
            // Protect buffer
            if (length >= (BUFFER_SIZE - 1)) return length;

            r = read(m_fd, (buffer + length), 1);

            if (r > 0)
            {
                length++;

                // Start timer
                timeout.start();
            }
        }

        return length;
    }

    void SerialPort::InitSpdLog()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/logger.txt", 1048, 10, true);

        std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
        spdlog::init_thread_pool(8192, 1);
        auto async_logger = std::make_shared<spdlog::async_logger>("async logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        async_logger->flush_on(spdlog::level::trace);

        spdlog::set_default_logger(async_logger);
    }

    void SerialPort::ClosePortLinux(void)
    {
        // Set old parameters
        tcsetattr(m_fd, TCSANOW, &m_oldtio);

        // Close serial port
        if (m_fd > 0)
        {
            close(m_fd);
        }
    }
#endif
}