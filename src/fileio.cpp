#include "include\fileio.h"
#include "include\device.h"
#include "include\measurementsession.h"

#define FOLDER_PREFIX "\\Measurement"
#define MEASUREMENT_FOLDER_PATH "C:\\Users\\USCT\\Desktop\\Works\\Measurements"
#define FOLDER_NAME_SEPERATOR "_"

void exportToCsv(std::vector<std::vector<double>> &data,
                 float h_scale,
                 int record_length,
                 std::string header,
                 char seperator,
                 std::string filename,
                 bool debug) {

    unsigned int i;
    // Calculating horizontal scale
    double h_step = h_scale*10/record_length;

    auto begin = std::chrono::steady_clock::now();

    // Aquiring filename
    std::string date = getDateString() + std::string(FOLDER_NAME_SEPERATOR) + getTimeString();
    std::string str_name = (getFolderString("NONE", date));
    std::wstring wstr_name = std::wstring(str_name.begin(), str_name.end());
    const wchar_t* name = wstr_name.c_str();
    CreateDirectory(name, NULL);
    std::string filepath = getFolderString(filename, date);

    // Opening and writing file
    std::ofstream outputFile(filepath, std::ofstream::out);
    if (debug) std::cout << "Writing curvedata to: " << filepath << "...\n";
    

    outputFile << "sep=" << seperator << std::endl;
    outputFile << "#curvedata.csv : " + getDateString() + " : " + getTimeString() << std::endl;
    outputFile << header;

    // Tableheaders
    outputFile << "time t";
    for (unsigned int i = 0; i < data.size(); i++) outputFile << seperator << "channel " << i;
    outputFile << std::endl;

    auto header_time = std::chrono::steady_clock::now();
    // Data


    for (i = 0; i < (data[0]).size(); i++) {

        outputFile << h_step*i;

        for (auto channel : data) outputFile << seperator << channel.at(i); //memcpy //buffered write
        outputFile << '\n';
    }

    auto data_time = std::chrono::steady_clock::now();

    std::cout << "Writing the header took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(header_time - begin).count()
              << "ms, writing data took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(data_time - header_time).count() << "ms\n";
    if (debug) std::cout << "Done!" << std::endl;
}

std::vector<float> importFromCSV(std::string date, std::string name, char seperator) {

    std::cout << "Loading CSV waveform file...";
    std::vector<float> waveform;
    std::ifstream inputFile(getFolderString(name, date));
    std::string line;
    char delim = seperator;

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') continue; // a bit dirty to skip seperator...
        if (line[0] == 's') {
            std::vector<std::string> sep = split(line, '=');
            delim = sep[1][0];
            continue;
        }
        std::vector<std::string> parts = split(line, delim);
        if (parts[0].empty()) continue;
        waveform.push_back(std::stof(parts[1]));
    }
    inputFile.close();
    std::cout << "Done!" << std::endl;
    return waveform;
}

std::string getTimeString() {

    time_t t = time(0);
    struct tm * now = localtime( & t );
    std::string hour = (now->tm_hour >= 10) ? std::to_string(now->tm_hour) : "0" + std::to_string(now->tm_hour);
    std::string min = (now->tm_min >= 10) ? std::to_string(now->tm_min) : "0" + std::to_string(now->tm_min);
    std::string sec = (now->tm_sec >= 10) ? std::to_string(now->tm_sec) : "0" + std::to_string(now->tm_sec);
    return hour + "-" + min + "-" + sec;
}

std::string getDateString() {

    time_t t = time(0);
    struct tm * now = localtime( & t );
    std::string year = std::to_string(now->tm_year + 1900);
    std::string month = (now->tm_mon + 1 > 10) ? std::to_string(now->tm_mon + 1) : "0" + std::to_string(now->tm_mon + 1);
    std::string day = (now->tm_mday >= 10) ? std::to_string(now->tm_mday) : "0" + std::to_string(now->tm_mday);
    return year + "-" + month + "-" + day;
}

std::string getFolderString(std::string filename, std::string &date) {

    std::string foldername = std::string(FOLDER_PREFIX) + std::string(FOLDER_NAME_SEPERATOR) + date;
    if (filename == "NONE") {
        return MEASUREMENT_FOLDER_PATH + foldername;
    } else {
        return MEASUREMENT_FOLDER_PATH + foldername + std::string("\\")  + filename;
    }

}

void importSettings(MeasurementSession &m, std::string date) {

    std::string filename = "settings.ses";

    std::ifstream infile(getFolderString(filename, date));
    if (!infile) {
        std::cout << "File could not be opened: " << getFolderString(filename, date) << std::endl;
        return;
    }
    if (m.getDebug()) std::cout << "Parsing settings file: " << date << std::endl;

    std::string line, device, manufacturer, address;

    while (std::getline(infile, line)) {

        if (line.c_str()[0] == '$') {
            const char* _line = line.c_str();
            _line += 1;
            line = std::string(_line);
            device = line;
        } else if (line.c_str()[0] == '=') {
            const char* _line = line.c_str();
            _line += 1;
            line = std::string(_line);
            address = line;
//            std::cout << address << std::endl;
        } else if (line.c_str()[0] == '%') {
            const char* _line = line.c_str();
            _line += 1;
            line = std::string(_line);
            m.addDevice(device, line, manufacturer, address);

        } else if (line.c_str()[0] == '&') {
            const char* _line = line.c_str();
            _line += 1;
            line = std::string(_line);
            manufacturer = line;

        } else if (line.c_str()[0] == '#') {
            continue;

        } else {
            std::vector<std::string> parts = split(line, ' ');
            m.setSetting(m.getDeviceByName(device), parts[0], parts[1]);
        }
    }
    infile.close();
    return;
}

void exportSettings(MeasurementSession &m) {

    std::ofstream outputFile;
    std::string date = getDateString() + std::string(FOLDER_NAME_SEPERATOR) + getTimeString();
    std::string filename = "settings.ses";
    std::string filepath = getFolderString(filename, date);

    outputFile.open(filepath);
    outputFile << "# Session settings file" << std::endl;
    std::map<std::shared_ptr<Device>, std::map<std::string, std::string>> devices = m.getSettings();

    for (auto device : devices) {
        std::map<std::string, std::string> settings = device.second;

        outputFile << std::string("$") << device.first.get()->getName() << std::endl;
        outputFile << std::string("%") << device.first.get()->getType() << std::endl;

        for (std::pair<std::string, std::string> setting : settings) {
            if (setting.first == "HEADER") continue;
            outputFile << setting.first << std::string(" ") << setting.second << std::endl;
        }

        outputFile << std::string("#") << std::endl << std::string("#") << std::endl;
    }
    outputFile.close();
    if (m.getDebug()) std::cout << "Session settings written to " << filepath << std::endl;
}

template<typename Out>

void split(const std::string &s, char delim, Out result) {

    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {

    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


