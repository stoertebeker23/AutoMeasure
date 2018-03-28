#include "include\device.h"

UART::UART() {

}

void UART::_write(std::string message) {

    DWORD dNoOFBytestoWrite;         // No of bytes to write into the port
    DWORD dNoOfBytesWritten = 0;     // No of bytes written to the port
    dNoOFBytestoWrite = message.length();
    char* msg = &message[0];
//    std::cout << "UART write " << msg << dNoOFBytestoWrite<< std::endl;

    if (WriteFile(hComm, msg, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL) != 1 ) {
        std::cout << "An error occurred while writing to UART" << std::endl;
    }
}

bool UART::establishConnection() {

    std::string ports = address;
    std::wstring portw = std::wstring(ports.begin(), ports.end());
    const wchar_t* port = portw.c_str();

    hComm = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, (wchar_t*)NULL);

    if (hComm == INVALID_HANDLE_VALUE) {
        std::cout << "Error in opening serial port " << hComm << std::endl;
        return false;
    } else {
        std::cout << "Establishing connection to UART at " << ports << std::endl;
    }

    DCB dcbSerialParams = { 0 }; // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

//    std::cout << GetCommState(hComm, &dcbSerialParams) << std::endl;

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    SetCommState(hComm, &dcbSerialParams);

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout         = 50; // in milliseconds
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    return false;
}

bool UART::closeConnection() {
    std::cout << "Closing connection to " << address << std::endl;
    CloseHandle(hComm);
    return true;
}

void UART::_identify() {
    std::cout << "UART detected!" << std::endl;
}
