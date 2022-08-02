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
	/*
	-- TODO --
	1. Show available COM ports
		* Example:
			SerialModule::SerialPort serial;
			std::vector<std::string> comPorts = serial.GetAvailablePorts();
	
	2. Send data from computer via connected port
		* Example:
			std::string data = "Hello from computer"
			serial.SendData(data.c_str());

	3. Run this library on linux
		* For OS Spesific situations use classes and polymorphism

	4. Use spdlog for logging

	5. Add function that closes open port
	*/
	
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
