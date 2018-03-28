#include "include\device.h"
#include "include\measurementsession.h"
#include "include\fileio.h"

#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\visa.h"

VISAWaveFormGenerator::VISAWaveFormGenerator() {

}

void VISAWaveFormGenerator::loadWaveformToDevice(std::string date) {

    std::vector<float> data = importFromCSV(date, "curvedata.csv", ',');
    std::string command = "DATA VOLATILE";
    for (auto & element : data) {
        command += ',';
        command += std::to_string(element);
    }
    std::cout << "Writing a lot of data to device! Actually " << command.length() * sizeof(std::string) << " bytes!" << std::endl;
    _write(command);
    _write("FUNC:SHAP USER");
}
