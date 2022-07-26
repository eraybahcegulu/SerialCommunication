#include <iostream>
#include <vector>

#include "SerialPort.h"

using namespace std;

SerialModule::SerialPort serial;
std::vector<int> comPorts = serial.GetAvailablePorts();

SerialModule::SerialPort port3("COM3", 115200);

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

	std::string data = "Hello from computer";
    port3.WriteData(data.c_str());

    if (port3.IsConnected()) {
        while (port3.IsConnected())
        {
        unsigned char comdata3;
        port3.ReceiveData(comdata3, 1);
        cout << comdata3;
        }
    }



}
