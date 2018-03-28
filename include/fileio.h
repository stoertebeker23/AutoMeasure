#ifndef FILEIO_H
#define FILEIO_H

#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <string>
#include <map>
#include <sstream>
#include <iterator>
#include <memory>
#include <chrono>

#define SINGLE_FOLDER 0
#define SINGLE_FILE 1

std::string getTimeString();
std::string getDateString();

// Forward declarations of used classes
class MeasurementSession;
class VISAOscilloscope;

// Export a vector of float data in CSV format. It will eventually create a new folder a fixed location. This folder
// will then contain the this CSV file with the curve data as well as the settings.ses file
// parameters:
//      std::shared_ptr<VISAOscilloscope> device: A pointer to the device the data was pulled from
//      std::vector<float> &data: the reference to the data pulled from the device
// returns:
//      void
// improvements:
//      - it doesnt need the device. The data should be handed over in a scaled format.
//      - either calculate the sampling frequency or hand a map with both x and y values
void exportToCsv(std::vector<std::vector<double> > &data, float h_scale, int record_length,
                 std::string header,
                 char seperator,
                 std::string filename,
                 bool debug);

// Import data from a CSV file. In this particular case the signal file for the waveformgenerator.
// parameters:
//      std::string date: the folder name which the signal file is read from
// returns:
//      std::vector<float>: the data read from the csv file
// improvements:
//      - streamline the csv file to also read the data pulled from the oszi as the signal
std::vector<float> importFromCSV(std::string date, std::string name, char seperator);

// Read the settings from the "settings.ses" file in a folder. The settings are then directly added to the measurement
// object the function is called from.
// parameters:
//      MeasurementSession &m: reference to the measurement object to add the settings to
//      std::string date: foldername date appendix which then specifies the folder to read from
// returns:
//      void
void importSettings(MeasurementSession &m,std::string date);

// Exports the settings to the settings.ses file. Creates a new folder if not already existing with current time and
// date.
// parameters:
//      MeasurementSession &m: reference to the measurement object export the settings from
// returns:
//      void
// improvements:
//      If the settings export and data exports are more than 1 second apart, a new folder is created. This is garbage
void exportSettings(MeasurementSession &m);

// Appends all parts of the folder or filename and returns it as one string. If filename is "NONE" it will only return
// the folder path
// parameters:
//      std::string filename: filename to append to the whole path
//      std::string &date: date appendix for the folder path
// returns:
//      std::string: concartinated folder or file path
std::string getFolderString(std::string filename, std::string &date);

template<typename Out>
void split(const std::string &s, char delim, Out result);
std::vector<std::string> split(const std::string &s, char delim);



#endif // FILEIO_H
