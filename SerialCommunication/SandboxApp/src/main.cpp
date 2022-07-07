#include <iostream>
#include "SerialPort.h"

using namespace std;

int main()
{
    choice:
    cout << "choice COM" << endl;
    cout << "COM3 -- 3" << endl;
    cout << "COM4 -- 4" << endl;
    cout << "COM5 -- 5" << endl;
    cout << "COM6 -- 6" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 3:
    {
        SerialModule::SerialPort port3("COM3", 115200);

        while (1)
        {
            unsigned char comdata3;
            port3.receive(comdata3, 1);
            cout << comdata3;
        }
        return 0;
    }
    break;
    case 4:
    {
        SerialModule::SerialPort port4("COM4", 115200);

        while (1)
        {
            unsigned char comdata4;
            port4.receive(comdata4, 1);
            cout << comdata4;
        }
        return 0;
    }
    break;
    case 5:
    {
        SerialModule::SerialPort port5("COM5", 115200);

        while (1)
        {
            unsigned char comdata5;
            port5.receive(comdata5, 1);
            cout << comdata5;
        }
        return 0;
    }
    break;
    case 6:
    {
        SerialModule::SerialPort port6("COM6", 115200);

        while (1)
        {
            unsigned char comdata6;
            port6.receive(comdata6, 1);
            cout << comdata6;
        }
        return 0;
    }
    break;
    default:
        cout << "3, 4, 5 veya 6 giriniz";
        goto choice;
    }
}
