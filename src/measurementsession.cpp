#include "include\measurementsession.h"
#include "include\device.h"
#include "include\fileio.h"
#include "include\algorythms.h"
#include "include\asic.h"
#include "include\measurementsession.h"

MeasurementSession::MeasurementSession(bool debug=false) {
    this->debug = debug;
}

void MeasurementSession::run(std::string session_name) {

    std::vector<std::vector<double>> data;

    // device pointers
    std::shared_ptr<VISAOscilloscope> scope;
    std::shared_ptr<VISAWaveFormGenerator> wfg;
    std::shared_ptr<VISAMultimeter> mult;
    std::shared_ptr<UART> uart;

    importSettings(*this, session_name);

    // Create pointers to devices and establish connections
    for (auto & element : devices) {
        if(element.second.get()->getType() == "oscilloscope") {

            scope = std::static_pointer_cast<VISAOscilloscope> (element.second);

            scope.get()->establishConnection();
        } else if(element.second.get()->getType() == "waveformgenerator") {

            wfg = std::static_pointer_cast<VISAWaveFormGenerator> (element.second);
            wfg.get()->establishConnection();
        } else if(element.second.get()->getType() == "multimeter") {

            mult = std::static_pointer_cast<VISAMultimeter> (element.second);
            mult.get()->establishConnection();
        } else if(element.second.get()->getType() == "uart") {

            uart = std::static_pointer_cast<UART> (element.second);
            uart.get()->establishConnection();
        }
    }

    // apply the settings for the device
    for (auto & element : devices) {
        if (element.second.get()->getType() == "uart") continue; //not implemented yet
        if (debug) element.second.get()->_identify();
        applySettings(element.first);
    }

    int data_chunk_size = 100000;
    int record_length = 1000000;

    scope->_write("HOR:RECO " + std::to_string(record_length));
    float h_scale = scope->_queryfloat("HOR:SCA?", 64);


    data.push_back(scope->getCurveDouble(data_chunk_size, 1, false));
    data.push_back(scope->getCurveDouble(data_chunk_size, 2, false));
    data.push_back(scope->getCurveDouble(data_chunk_size, 3, false));
    data.push_back(scope->getCurveDouble(data_chunk_size, 4, false));

    std::map<std::string, float> param;
    exportToCsv(data,
                h_scale,
                record_length,
                returnFileHeader(200.0, 0.1, 0.1, param),
                ',',
                "curvedata.csv",
                debug);

    exportSettings(*this);
    for (auto & element : devices) element.second.get()->closeConnection();
}

std::string MeasurementSession::returnFileHeader (float frequency,
                                                  float amplitude,
                                                  float offset,
                                                  std::map<std::string, float> parameters) {

    std::string header = "# Frequency: " + std::to_string(frequency) + "Hz\n" +
                         "# Amplitude: " + std::to_string(amplitude) + "V \n" +
                         "# Offset:    " + std::to_string(offset)     + "V \n";

    if(parameters.empty()) return header;

    for (auto parameter : parameters) {
        header += '#'
                + parameter.first
                + std::to_string(parameter.second)
                + '\n';
    }

    return header;
}
void MeasurementSession::setSetting (std::shared_ptr<Device> device, std::string setting, std::string value) {

    std::map<std::shared_ptr<Device>,std::map<std::string, std::string>>::iterator device_it;
    std::map<std::string, std::string>::iterator setting_it;
    device_it = settings.find(device);

    if (device_it == settings.end()) settings[device].insert(std::make_pair(setting, "0.0"));

    setting_it = settings[device].find(setting);
    if (setting_it == settings[device].end()) settings[device].insert(std::make_pair(setting, "0.0"));

    settings.at(device).at(setting) = value;
    if (debug) std::cout << "Setting: " << device.get()->getName() << " " << setting << " " << value << std::endl;
}

void MeasurementSession::applySettings (std::string device) {
    if (debug) std::cout << "Trying to apply settings for " << device << "...";
    // BEHOLD!!
    auto it = std::find_if(settings.begin(), settings.end(), [&device](std::pair<const std::shared_ptr<Device>,
                           std::map<std::string, std::string> >& obj) {return obj.first.get()->getName() == device;});

    std::map<std::string, std::string> l_settings = settings.at(it->first);
    for (std::pair<std::string, std::string> element : l_settings) {
        if (element.first == "address") continue;
        std::cout << "Writing: " << element.first + std::string(" ") + element.second << std::endl;
        it->first.get()->_write(element.first + std::string(" ") + element.second);
        // can be done easier over the devices list....
    }
    if (debug) std::cout << "Done!" << std::endl;
}

void MeasurementSession::addDevice (std::string &name, std::string type, std::string manufacturer, std::string address) {

    if (type == "oscilloscope") {

        std::shared_ptr<VISADevice> device_ptr (new VISAOscilloscope);
        devices.insert(std::make_pair(name, device_ptr));
        device_ptr.get()->setName(name);
        device_ptr.get()->setType(type);
        device_ptr.get()->setAddress(address);
        device_ptr.get()->setManufacturer(manufacturer);
        setSetting(device_ptr, "address", address);

    } else if (type == "waveformgenerator") {

        std::shared_ptr<VISADevice> device_ptr (new VISAWaveFormGenerator);
        devices.insert(std::make_pair(name, device_ptr));
        device_ptr.get()->setName(name);
        device_ptr.get()->setType(type);
        device_ptr.get()->setAddress(address);
        device_ptr.get()->setManufacturer(manufacturer);
        setSetting(device_ptr, "address", address);

    } else if (type == "uart") {

        std::shared_ptr<Device> device_ptr (new UART);
        devices.insert(std::make_pair(name, device_ptr));
        device_ptr.get()->setName(name);
        device_ptr.get()->setType(type);
        device_ptr.get()->setAddress(address);
        setSetting(device_ptr, "address", address);

    } else if (type == "multimeter") {

        std::shared_ptr<VISADevice> device_ptr (new VISAMultimeter);
        devices.insert(std::make_pair(name, device_ptr));
        device_ptr.get()->setName(name);
        device_ptr.get()->setType(type);
        device_ptr.get()->setAddress(address);
        device_ptr.get()->setManufacturer(manufacturer);
        setSetting(device_ptr, "address", address);
    }
    if (debug) std::cout << "Adding device of type " << type << " with name " << name << std::endl;
}

std::map<std::shared_ptr<Device>, std::map<std::string, std::string> > MeasurementSession::getSettings () const {
    return settings;
}

std::shared_ptr<Device> MeasurementSession::getDeviceByName (std::string device) {
    return devices.at(device);
}

bool MeasurementSession::getDebug () {
    return debug;
}
