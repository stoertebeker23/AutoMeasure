#include <string>
#include "include\device.h"

Device::Device() {

}

std::string Device::getName() const {

    return name;
}

void Device::setName(const std::string &name_) {

    name = name_;
}

std::string Device::getType() const {

    return type;
}

void Device::setType(const std::string &type_) {

    type = type_;
}

std::string Device::getAddress() const {

    return address;
}

void Device::setAddress(const std::string &address_) {

    address = address_;
}
