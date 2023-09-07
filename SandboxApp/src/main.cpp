#include "SerialPort.h"
#include "spdlog/spdlog.h"

using namespace std;

#define MAX_BUFFER_SIZE 255
uint8_t incoming_data[MAX_BUFFER_SIZE];

#ifdef WINDOWS
const long BaudRate = 9600;
#endif

int main()
{
#ifdef WINDOWS
    SerialModule::SerialPort Ports;
    Ports.GetAvailablePorts();

    SerialModule::SerialPort Logs;
    Logs.InitSpdLog();

    string data;
    string com;
    int baudRate;

    spdlog::info("Enter Active COM Port (COM1, COM2...): ");
    cin >> com;

    spdlog::info("Enter Baud Rate (9600, 115200...): ");
    cin >> baudRate;

    spdlog::info("COM Port entered by the user: {}", com);
    spdlog::info("Baud Rate entered by the user: {}", baudRate);

    SerialModule::SerialPort port;
    port.Initialize(com.c_str(), BaudRate);

    spdlog::info("Enter the data to be sent: ");
    cin >> data;
    port.WriteData(data.c_str());

    spdlog::info("Sent data to {}: {}", com, data);

    if (port.IsConnected())
    {
        port.ReceiveData(incoming_data, MAX_BUFFER_SIZE);
        spdlog::info("Received data from {}: {}", com, incoming_data);
    }

    port.CloseSerialPort(com.c_str());

    if (port.IsConnected())
    {
        spdlog::warn("{} still open", com);
    }
#endif
    return 0;
}
