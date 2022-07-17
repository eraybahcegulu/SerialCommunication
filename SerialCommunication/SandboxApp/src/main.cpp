#include <iostream>
#include "SerialPort.h"

using namespace std;

int main()
{
    SerialModule::SerialPort();
    SerialModule::SerialPort port3("COM3", 115200);
    SerialModule::SerialPort port4("COM4", 115200);
    SerialModule::SerialPort port5("COM5", 115200);
    SerialModule::SerialPort port6("COM6", 115200);

    if (port3.isConnected())
    {
        cout << endl << "COM3" << endl;
        while (port3.isConnected())
        {
            unsigned char comdata3;
            port3.receive(comdata3, 1);
            cout << comdata3;
        }
    }

    if (port4.isConnected())
    {
        cout << endl << "COM4" << endl;
        while (port4.isConnected())
        {
            unsigned char comdata4;
            port4.receive(comdata4, 1);
            cout << comdata4;
        }
    }

    if (port5.isConnected())
    {
        cout << endl << "COM5" << endl;
        while (port5.isConnected())
        {
            unsigned char comdata5;
            port5.receive(comdata5, 1);
            cout << comdata5;
        }
    }

    if (port6.isConnected())
    {
        cout << endl << "COM6" << endl;
        while (port6.isConnected())
        {
            unsigned char comdata6;
            port6.receive(comdata6, 1);
            cout << comdata6;
        }
    }
}
