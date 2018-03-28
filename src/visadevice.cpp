#include "include\device.h"
#include "include\fileio.h"

#include <iostream>


VISADevice::VISADevice() {

    // Own error codes
    errormap.insert(std::pair<signed long, std::string>(-1, "FIRST_CHAR_INVALID"));
    errormap.insert(std::pair<signed long, std::string>(-2, "ELEMENT_FIELD_WIDTH_OUT_OF_RANGE"));
    // Visa error codes
    errormap.insert(std::pair<signed long, std::string>(-1073807360,"VI_ERROR_SYSTEM_ERROR"));
    errormap.insert(std::pair<signed long, std::string>(-1073807346,"VI_ERROR_INV_OBJECT"));
    errormap.insert(std::pair<signed long, std::string>(-1073807345,"VI_ERROR_RSRC_LOCKED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807344,"VI_ERROR_INV_EXPR"));
    errormap.insert(std::pair<signed long, std::string>(-1073807343,"VI_ERROR_RSRC_NFOUND"));
    errormap.insert(std::pair<signed long, std::string>(-1073807342,"VI_ERROR_INV_RSRC_NAME"));
    errormap.insert(std::pair<signed long, std::string>(-1073807341,"VI_ERROR_INV_ACC_MODE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807339,"VI_ERROR_TMO"));
    errormap.insert(std::pair<signed long, std::string>(-1073807338,"VI_ERROR_CLOSING_FAILED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807333,"VI_ERROR_INV_DEGREE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807332,"VI_ERROR_INV_JOB_ID"));
    errormap.insert(std::pair<signed long, std::string>(-1073807331,"VI_ERROR_NSUP_ATTR"));
    errormap.insert(std::pair<signed long, std::string>(-1073807330,"VI_ERROR_NSUP_ATTR_STATE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807329,"VI_ERROR_ATTR_READONLY"));
    errormap.insert(std::pair<signed long, std::string>(-1073807328,"VI_ERROR_INV_LOCK_TYPE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807327,"VI_ERROR_INV_ACCESS_KEY"));
    errormap.insert(std::pair<signed long, std::string>(-1073807322,"VI_ERROR_INV_EVENT"));
    errormap.insert(std::pair<signed long, std::string>(-1073807321,"VI_ERROR_INV_MECH"));
    errormap.insert(std::pair<signed long, std::string>(-1073807320,"VI_ERROR_HNDLR_NINSTALLED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807319,"VI_ERROR_INV_HNDLR_REF"));
    errormap.insert(std::pair<signed long, std::string>(-1073807318,"VI_ERROR_INV_CONTEXT"));
    errormap.insert(std::pair<signed long, std::string>(-1073807315,"VI_ERROR_QUEUE_OVERFLOW"));
    errormap.insert(std::pair<signed long, std::string>(-1073807313,"VI_ERROR_NENABLED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807312,"VI_ERROR_ABORT"));
    errormap.insert(std::pair<signed long, std::string>(-1073807308,"VI_ERROR_RAW_WR_PROT_VIOL"));
    errormap.insert(std::pair<signed long, std::string>(-1073807307,"VI_ERROR_RAW_RD_PROT_VIOL"));
    errormap.insert(std::pair<signed long, std::string>(-1073807306,"VI_ERROR_OUTP_PROT_VIOL"));
    errormap.insert(std::pair<signed long, std::string>(-1073807305,"VI_ERROR_INP_PROT_VIOL"));
    errormap.insert(std::pair<signed long, std::string>(-1073807304,"VI_ERROR_BERR"));
    errormap.insert(std::pair<signed long, std::string>(-1073807303,"VI_ERROR_IN_PROGRESS"));
    errormap.insert(std::pair<signed long, std::string>(-1073807302,"VI_ERROR_INV_SETUP"));
    errormap.insert(std::pair<signed long, std::string>(-1073807301,"VI_ERROR_QUEUE_ERROR"));
    errormap.insert(std::pair<signed long, std::string>(-1073807300,"VI_ERROR_ALLOC"));
    errormap.insert(std::pair<signed long, std::string>(-1073807299,"VI_ERROR_INV_MASK"));
    errormap.insert(std::pair<signed long, std::string>(-1073807298,"VI_ERROR_IO"));
    errormap.insert(std::pair<signed long, std::string>(-1073807297,"VI_ERROR_INV_FMT"));
    errormap.insert(std::pair<signed long, std::string>(-1073807295,"VI_ERROR_NSUP_FMT"));
    errormap.insert(std::pair<signed long, std::string>(-1073807294,"VI_ERROR_LINE_IN_USE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807293,"VI_ERROR_LINE_NRESERVED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807290,"VI_ERROR_NSUP_MODE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807286,"VI_ERROR_SRQ_NOCCURRED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807282,"VI_ERROR_INV_SPACE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807279,"VI_ERROR_INV_OFFSET"));
    errormap.insert(std::pair<signed long, std::string>(-1073807278,"VI_ERROR_INV_WIDTH"));
    errormap.insert(std::pair<signed long, std::string>(-1073807276,"VI_ERROR_NSUP_OFFSET"));
    errormap.insert(std::pair<signed long, std::string>(-1073807275,"VI_ERROR_NSUP_VAR_WIDTH"));
    errormap.insert(std::pair<signed long, std::string>(-1073807273,"VI_ERROR_WINDOW_NMAPPED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807271,"VI_ERROR_RESP_PENDING"));
    errormap.insert(std::pair<signed long, std::string>(-1073807265,"VI_ERROR_NLISTENERS"));
    errormap.insert(std::pair<signed long, std::string>(-1073807264,"VI_ERROR_NCIC"));
    errormap.insert(std::pair<signed long, std::string>(-1073807263,"VI_ERROR_NSYS_CNTLR"));
    errormap.insert(std::pair<signed long, std::string>(-1073807257,"VI_ERROR_NSUP_OPER"));
    errormap.insert(std::pair<signed long, std::string>(-1073807256,"VI_ERROR_INTR_PENDING"));
    errormap.insert(std::pair<signed long, std::string>(-1073807254,"VI_ERROR_ASRL_PARITY"));
    errormap.insert(std::pair<signed long, std::string>(-1073807253,"VI_ERROR_ASRL_FRAMING"));
    errormap.insert(std::pair<signed long, std::string>(-1073807252,"VI_ERROR_ASRL_OVERRUN"));
    errormap.insert(std::pair<signed long, std::string>(-1073807250,"VI_ERROR_TRIG_NMAPPED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807248,"VI_ERROR_NSUP_ALIGN_OFFSET"));
    errormap.insert(std::pair<signed long, std::string>(-1073807247,"VI_ERROR_USER_BUF"));
    errormap.insert(std::pair<signed long, std::string>(-1073807246,"VI_ERROR_RSRC_BUSY"));
    errormap.insert(std::pair<signed long, std::string>(-1073807242,"VI_ERROR_NSUP_WIDTH"));
    errormap.insert(std::pair<signed long, std::string>(-1073807240,"VI_ERROR_INV_PARAMETER"));
    errormap.insert(std::pair<signed long, std::string>(-1073807239,"VI_ERROR_INV_PROT"));
    errormap.insert(std::pair<signed long, std::string>(-1073807237,"VI_ERROR_INV_SIZE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807232,"VI_ERROR_WINDOW_MAPPED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807231,"VI_ERROR_NIMPL_OPER"));
    errormap.insert(std::pair<signed long, std::string>(-1073807229,"VI_ERROR_INV_LENGTH"));
    errormap.insert(std::pair<signed long, std::string>(-1073807215,"VI_ERROR_INV_MODE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807204,"VI_ERROR_SESN_NLOCKED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807203,"VI_ERROR_MEM_NSHARED"));
    errormap.insert(std::pair<signed long, std::string>(-1073807202,"VI_ERROR_LIBRARY_NFOUND"));
    errormap.insert(std::pair<signed long, std::string>(-1073807201,"VI_ERROR_NSUP_INTR"));
    errormap.insert(std::pair<signed long, std::string>(-1073807200,"VI_ERROR_INV_LINE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807199,"VI_ERROR_FILE_ACCESS"));
    errormap.insert(std::pair<signed long, std::string>(-1073807198,"VI_ERROR_FILE_IO"));
    errormap.insert(std::pair<signed long, std::string>(-1073807197,"VI_ERROR_NSUP_LINE"));
    errormap.insert(std::pair<signed long, std::string>(-1073807196,"VI_ERROR_NSUP_MECH"));
    errormap.insert(std::pair<signed long, std::string>(-1073807195,"VI_ERROR_INTF_NUM_NCONFIG"));
    errormap.insert(std::pair<signed long, std::string>(-1073807194,"VI_ERROR_CONN_LOST"));
    errormap.insert(std::pair<signed long, std::string>(-1073807193,"VI_ERROR_MACHINE_NAVAIL"));
    errormap.insert(std::pair<signed long, std::string>(-1073807192,"VI_ERROR_NPERMISSION"));
}

bool VISADevice::establishConnection() {

    ViStatus status;
    std::cout << "Establishing connection to Device at " << address << "...";
    if ((status = viOpenDefaultRM(&defaultRM)) < VI_SUCCESS) error(status);
    if ((status = viOpen(defaultRM, (ViRsrc)address.c_str(), VI_NULL, VI_NULL, &instrument)) < VI_SUCCESS) {
        error(status);
        exit (EXIT_FAILURE);
    }
    std::cout << "Done!" << std::endl;
    return true;
}

bool VISADevice::closeConnection() {

    ViStatus status;
    std::cout << "Closing connection to Device at " << address << "...";
    if ((status = viClose(instrument)) < VI_SUCCESS) {
        error(status);
        std::cout <<" failed" << std::endl;
    }
    if ((status = viClose(defaultRM)) < VI_SUCCESS) {
        error(status);
       std::cout <<" failed" << std::endl;
}
    std::cout << "Done!" << std::endl;
    return true;
}

void VISADevice::error() {

    std::cout << "An error occurred!" << std::endl;
}

void VISADevice::error(ViStatus &status) {

    auto message = errormap.find(status);
    if (message != errormap.end()) {
        std::cout << "An error occurred! Error message: " << message->second << std::endl;
    } else {
        std::cout << "An error occurred! Error message not listed: " << status << std::endl;
    }
}

void VISADevice::_identify() {

    std::vector<std::string> name_string = split(_query("*idn?", 64, true), '\n');
    std::cout << "Device name: " << name_string[0] << std::endl;
}



void VISADevice::_write(std::string command) {

    ViStatus status;
    const char* array = command.c_str();
    if ((status = viWrite(instrument, ViBuf(array), command.length(), &retCnt)) < VI_SUCCESS) error(status);
    if ((status = viFlush(instrument, VI_WRITE_BUF)) < VI_SUCCESS) error(status);
    std::cout << "Writing: " << command << " to " << instrument << std::endl;
}

void VISADevice::setManufacturer(const std::string &manufacturer) {
    this->manufacturer = manufacturer;
}

char* VISADevice::_query(std::string command, int num_bytes, bool flush) {

    ViStatus status;
    if (flush) {
        char x = '0';
        if ((status = viFlush(instrument, VI_READ_BUF)) < VI_SUCCESS) {
            error(status);
            return &x;
        }
    }
    _write(command);
    return _read(num_bytes);
}

float VISADevice::_queryfloat(std::string command, int num_bytes) {

    char * retVal = _query(command, num_bytes, true);
    return atof(retVal);
}

char* VISADevice::_read(int num_bytes) {

    ViStatus status;
    char * readBuffer = (char*) malloc((num_bytes + 1) * sizeof(char));

    if ((status = viRead(instrument, (ViPBuf) readBuffer, num_bytes, &retCnt)) < VI_SUCCESS) error(status);
    return readBuffer;
}


