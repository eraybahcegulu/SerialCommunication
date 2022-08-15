#include "SerialPort.h"

using namespace std;

#define MAX_BUFFER_SIZE 255
uint8_t incoming_data[MAX_BUFFER_SIZE];

#ifdef WINDOWS
const char* com = "COM5";
const long BaudRate = 115200;
#endif

int main()
{
    SerialModule::SerialPort Logs;
    SerialModule::SerialPort Ports;

    Logs.InitSpdLog();
    Ports.GetAvailablePorts();
    SerialModule::SerialPort port(com, BaudRate);

    

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
}