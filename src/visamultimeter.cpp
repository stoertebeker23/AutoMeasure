#include "include\device.h"

#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\visa.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\TekVisa.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\visatype.h"
#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include\vpptype.h"

VISAMultimeter::VISAMultimeter() {
}

float VISAMultimeter::measureVoltage(float range, bool type) {
    if(range < 0.1 && range > 1000) {
        std::cout << "Multimeter: Range limits exeeced\n";
        return 0.0;
    }

    _write("CONF:" + std::string(type ? "DC" : "AC"));
    _write("CONF:VOLT " + std::to_string(range));

//   _write("INIT");
   Sleep(1000);
    return _queryfloat("MEAS:VOLT?", 64);
//    return _queryfloat("FETC?", 64);
}

float VISAMultimeter::measureCurrent(int range, bool type) {
    if(range < 0.1 && range > 1000) {
        std::cout << "Multimeter: Range limits exeeced\n";
        return 0.0;
    }

    _write("CONF:" + std::string(type ? "DC" : "AC") + "\n");
    _write("CONF:VAST " + std::to_string(range));
    return _queryfloat("MEAS:VOLT?", 64);
}
//float VISAMultimeter::measurecap(ccctype) {
//    if(range < 0.1 && range > 1000) {
//        std::cout << "Multimeter: Range limits exeeced\n";
//        return 0.0;
//    }

//    _write("CONF:" + std::string(type ? "DC" : "AC") + "\n");
//    _write("CONF:VOAS " + std::to_string(range));
//    return _queryfloat("MEAS:VOLT?", 64);
//}

//float VISAMultimeter::measureVoltage(int range, bool type) {
//    if(range < 0.1 && range > 1000) {
//        std::cout << "Multimeter: Range limits exeeced\n";
//        return 0.0;
//    }

//    _write("CONF:" + std::string(type ? "DC" : "AC") + "\n");
//    _write("CONF:VOLT " + std::to_string(range));
//    return _queryfloat("MEAS:VOLT?", 64);
//}
