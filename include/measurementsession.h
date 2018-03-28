#ifndef MEASUREMENTSESSION_H
#define MEASUREMENTSESSION_H

#include <map>
#include <string>
#include <vector>
#include <time.h>
#include <memory>
#include <algorithm>
#include <Windows.h>

// Forward declarations of used classes
class VISADevice;
class Device;
class UART;

class MeasurementSession {
public:
    MeasurementSession(bool debug);

    // Gets executed from the main and contains the measurement. So connecting to devices, pulling data, working with that
    // data and saving it. No actual device communication is working here, nor any direct file output.
    // parameters:
    //      std::string session name: date of measurement session to load in format "YYYY-MM-DD_HH-MM-SS"
    // returns:
    //      void
    void run(std::string session_name);

    // Adds a setting to a device in the settings map. With VISA Devices it is only a VISA command specified in the many
    // programming references of Tektronix and Keysight. Sth. like "CH1_SCALE 10".
    // The function will add the devicepointer to the list if it not inside the map and will add the setting if it is not
    // already there. It will change existing settings to the new value.
    // parameters:
    //      std::shared_ptr<Device> device: A pointer to the device which the setting is meant to be sent to
    //      std::string setting: The setting which can be applied lateron.
    //      std::string value: The value of the setting. At this time mostly unused
    // returns:
    //      void
    void setSetting(std::shared_ptr<Device> device,
                     std::string setting,
                     std::string value);

    // Synchronize the setting list with the settings on the device. This means iterating through the settings list and
    // sending every setting over to the devices. There is no confirmation from the devices, so always make sure that
    // everything is set correctly and no errors occured.
    // parameters:
    //      std::string device: name of the device to send the settings to.
    // returns:
    //      void
    void applySettings(std::string device);

    std::map<std::shared_ptr<Device>, std::map<std::string, std::string>> getSettings() const;

    // Method to initially construct a new device object depending on the type specified in the settings.ses file in
    // corresponding measrement folder.
    // parameters:
    //      std::string &name: name of the device to be created.
    //      std::string type: type of the device.
    // returns:
    //      void
    void addDevice(std::string &name,
                   std::string type,
                   std::string manufacturer,
                   std::string address);

    std::shared_ptr<Device> getDeviceByName(std::string device);
    bool getDebug();

    //
    std::string returnFileHeader(float frequency,
                                 float amplitude,
                                 float offset,
                                 std::map<std::string, float> parameters);
private:
    // If debug printouts should be active or not
    bool debug;

    // Contains device pointers and settings for a device. Mainly contains VISA library commands.
    std::map <std::shared_ptr<Device>, std::map<std::string, std::string>> settings;

    // Maps names to device pointers for easier access
    std::map <std::string, std::shared_ptr<Device>> devices;
};

#endif // MEASUREMENTSESSION_H
