#include "SerialPort.h"

using namespace std;

#define MAX_BUFFER_SIZE 255
uint8_t incoming_data[MAX_BUFFER_SIZE];

#ifdef WINDOWS
const char* com = "COM5";
const long BaudRate = 115200;
#endif

#ifdef LINUX
char* port = "/dev/ttyUSB0";
int BaudRate = 9600;
char Bits = 8;
char StopBit = 1;
#endif

int main()
{
    SerialModule::SerialPort Logs;
    Logs.InitSpdLog();

#ifdef WINDOWS
    SerialModule::SerialPort Ports;
    Ports.GetAvailablePorts();

    SerialModule::SerialPort port;
    port.Initialize(com, BaudRate);

    std::string data = "Hello from computer";
    port.WriteData(data.c_str());

    if (port.IsConnected())
    {
        port.ReceiveData(incoming_data, MAX_BUFFER_SIZE);
        spdlog::info("Received data from {}: {}", com , incoming_data);
    }

    port.CloseSerialPort(com);

    if (port.IsConnected())
    {
        spdlog::warn("{} still open", com);
    }
#endif

#ifdef LINUX
    char buffer[256] = { 0 };
    int i, length = 0;
    SerialModule::SerialPort port;
    port.OpenPortLinux(port, BaudRate, Bits, NO, StopBit);
    while (1)
    {
        // Wait character
        length = port.ReadData(buffer);

        if (length)
        {
            for (i = 0; i < length; i++)
            {
                printf("%.2X ", buffer[i]);
                //printf("%c", buffer[i]);
            }

            printf("\n");

            // Send data
            port.WriteData(buffer, length);
        }
    }
    port.ClosePortLinux();

    return 0;

#endif
}