# CppSerialCommunication

## Description

Library for communicating with COM ports on a Windows system.

* `premake` based build system

## Building Using Premake

1. Clone the git repository onto your local storage.

1. Include the spdlog library 

    ```
    SerialCommunication/vendor/spdlog
	```

1. Change into root repository directory

    ```
	$ cd SerialCommunication
	```

1. Generate project files by running a command like this one

    ```
	$ premake5 vs2019
	```

## Examples

    ```c++
	#include <iostream>
    #include <vector>

    #include "SerialPort.h"

    using namespace std;

    #define MAX_BUFFER_SIZE 255
    uint8_t incoming_data[MAX_BUFFER_SIZE];

    const char* com = "COM3";
    const long BaudRate = 9600;

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
	```