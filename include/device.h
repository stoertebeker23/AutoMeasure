#ifndef DEVICE_H
#define DEVICE_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <windows.h>
#include <stdio.h>

#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\visa.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\visatype.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\vpptype.h"
//#include "dualVisa.h"

#define AC false
#define DC true

class Device {
public:
    Device();

    std::string getName() const;

    void setName(const std::string &name_);

    std::string getType() const;

    void setType(const std::string &type_);

    std::string getAddress() const;

    void setAddress(const std::string &address_);

//    virtual void setManufacturer (const std::string manufacturer) = 0;

    virtual void _write(std::string command) = 0;

    virtual bool establishConnection() = 0;

    virtual bool closeConnection() = 0;

    virtual void _identify() = 0;

protected:
    std::string name;
    std::string type;
    std::string address;
};

class VISADevice : public Device {
public:
    VISADevice();

    // This method is called from the derivated method. The derivated object contains the Devices USB address.
    // The method then opens a new VISA defaultRM and instrument and connects to it.
    // parameters:
    //      std::string address: VISADevice's USB address as a string
    // returns:
    //      bool: always true...to be implemented
    bool establishConnection();

    // Closes the connection to a VISA Device specified with the address parameter
    // parameters:
    //      std::string address: VISADevice's USB address as a string
    // returns:
    //      bool: always true...to be implemented
    bool closeConnection();

    // Writes to a device specified in the VISADevice object's instrument variable. It writes a char* to the device
    // and then flushes the device's write buffer.
    // parameters:
    //      std::string command: the VISA command to write to the device
    // returns:
    //      void
    void _write(std::string command);

    void setManufacturer(const std::string &manufacturer);

    // This method will write a command to the devices and then read the answer. It flushed the readBuffer, then calls
    // the _write method with the command specified in the parameters. The it returns the char* read from the device
    // via _read(int num_bytes).
    // parameters:
    //      std::string command: The command to trigger a writeout by the device such as "curve?"
    //      int num_bytes: number of bytes to read from the device
    //      bool flush: specifies if the read buffer should be flushed or not
    // returns:
    //      char*: the char array which is read from the device
    char* _query(std::string command, int num_bytes, bool flush);

    // Casts the return value of _query() to float and will flush the read buffer because a float is not that long
    // parameters:
    //      std::string command: The command to trigger a writeout by the device such as "curve?"
    //      int num_bytes: number of bytes to read from the device
    // returns:
    //      float: the read char from the device which is casted to float
    float _queryfloat(std::string command, int num_bytes);

    // reads from the device, is only used by the query function. there is not much use anywhere eles.
    // parameters:
    //      int num_bytes: number of bytes to read from the device.
    // returns:
    //      char*: the char array which is read from the device
    char* _read(int num_bytes);

    // Just prints out that an error occurred
    // parameters:
    //      void
    // returns:
    //      void
    void error();

    // Looks up the status message returned by the VISA Methods inseide the error message map. Also maps some own error
    // codes to error messages
    // parameters:
    //      ViStatus &status: the status returned by a visa function. Its bigger then 0 if successfull
    // returns:
    //      void
    void error(ViStatus &status);

    // Queries "*idn?* to the device to get the name, manufacturer and ID. Then prints it to the console.
    // parameters:
    //      void
    // returns:
    //      void
    void _identify();

protected:

    std::string manufacturer;

    // Needed to open VISA connections to a device, nothing happens with this variable
    ViSession defaultRM;

    // The instrument session for a device. This session is specified in every ViRead or ViWrite call
    ViSession instrument;

    // Return count of the read bits by ViRead()
    ViUInt32 retCnt;

    // Contains all error codes for the VISA Oscilloscope and some self defined.
    std::map<signed long, std::string> errormap;
};

class UART : public Device {
public:

    UART();

    // Writes a char* to a device connected via uart.
    // parameters:
    //      std::string message: The char array to write over the UART line.
    // returns:
    //      void
    void _write(std::string message);

    // TODO
    // parameters:
    //      std::string address: comport of the computer
    // returns:
    //      void
    bool establishConnection();

    // Close UART handle
    // parameters:
    //      std::string address: comport of the computer
    // returns:
    //      void
    bool closeConnection();

    // Only prints out stuff, should ask for information from the MSP
    // parameters:
    //      void
    // returns:
    //      void
    void _identify();

    void setManufacturer(const std::string manufacturer);

private:

    // UART Handle
    HANDLE handle_uart;
};

class VISAOscilloscope : public VISADevice {
public:

    VISAOscilloscope();

    // Writes "curve?" to the devices and writes both data start and data stop settings to device according to the
    // length parameter. The method will then read a number of bytes, specified in lenght, from the device.
    // parameters:
    //      int length: number of bytes of curve data to get from the device
    // returns:
    //      the characters read from the device.
    char *getCurve(int length);
    std::vector<double> getCurveDouble(int length, short channel, bool true_osci_screen_offset);
};

class VISAWaveFormGenerator : public VISADevice {
public:
    VISAWaveFormGenerator();

    // Loads a waveform extracted from a csv file to the waveformgenerator.
    //
    // parameters:
    //      std::string date: The folder to load the chrip.csv file from
    // returns:
    //      void
    void loadWaveformToDevice(std::string date);

};

class VISAMultimeter : public VISADevice {
public:
    VISAMultimeter();

    float measureVoltage(float range, bool type);
    float measureCurrent(int range, bool type);
};

#endif // DEVICE_H
