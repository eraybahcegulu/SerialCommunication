#include <iostream>
#include "SerialPort.hpp"

using namespace std;

int main()
{
    SerialPort port("COM4", 115200);

    while (1)
    {
        unsigned char data;
        port.receive(data, 1);
        cout << data;
    }
    return 0;
}
