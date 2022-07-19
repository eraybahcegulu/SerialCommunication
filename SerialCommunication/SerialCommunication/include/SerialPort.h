#include <windows.h>
#include <iostream>


namespace SerialModule
{
    class SerialPort
    {
        public:
        //Constructors
        SerialPort();
        SerialPort(const char* port, unsigned long BaudRate); //the constructor that set up the serial port

        //Initialization
        void Initialize(const char* port, unsigned long BaudRate); //initialize serial port connection

        //Serial I/O
        void receive(unsigned char& data, unsigned int byteSize); //receives serial port data

        //Destructor
        ~SerialPort();

        bool isConnected(); //Check if we are actually connected

        private:
        HANDLE handler;
        bool isConnect;

};

}
