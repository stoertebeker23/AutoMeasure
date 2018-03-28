#include "include\device.h"

#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\visa.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\visatype.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\vpptype.h"

VISAOscilloscope::VISAOscilloscope() {

}

char* VISAOscilloscope::getCurve(int length) {

    _write("data:start 1");
    _write("data:stop " + std::to_string(length));
    float len_digits = length;
    int i = 3; // #-byte, length byte plus first data width byte (structure: #<length of width><width> e.g. #41000 for 1000 bytes)
    while (len_digits > 9.9) {
        len_digits /= 10;
        i++; // loop for setting the data header bytes correct amount.

    }
    std::cout << "VISA: Getting " << length+i << " bytes from device..." << std::endl;
    return _query("CURV?", length+i, true)+i;
}

std::vector<double> VISAOscilloscope::getCurveDouble(int length, short channel, bool true_osci_screen_offset) {
    std::vector<double> data;
    // select channel
    _write("DAT:SOU CH" + std::to_string(channel));
    // binary data
    char *curvedata = getCurve(2*length);
    // scaling
    float y_mult = _queryfloat("wfmoutpre:ymult?", 64);
    float y_off = _queryfloat("wfmoutpre:yoff?", 64);

//    std::cout << y_mult << " " << y_off*y_mult << std::endl;

    for (int i = 0; i < 2*length; i+=2) {

        int value = curvedata[i+1] << 8;
        value |= curvedata[i] & 0b0000000011111111;

        if (true_osci_screen_offset) {
            data.push_back(value*y_mult);
        } else {
            data.push_back(value*y_mult-y_off*y_mult);
        }
    }
    return data;
}
