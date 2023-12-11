#include "Bot.hpp"

Bot::Bot(std::string deviceId, std::string deviceName, std::string macAddress, std::vector<std::string> ipAddresses)
    : DEVICE_ID(deviceId), DEVICE_NAME(deviceName), MAC_ADDRESS(macAddress), IP_ADDRESSES(ipAddresses) {
    this->DEVICE_ID = deviceId;
    this->DEVICE_NAME = deviceName;
    this->MAC_ADDRESS = macAddress;
    this->IP_ADDRESSES = ipAddresses;
}

Bot::Bot() {};

// Getter for Device ID
std::string Bot::getDeviceId() const {
    return this->DEVICE_ID;
}

// Getter for Device Name
std::string Bot::getDeviceName() const {
    return this->DEVICE_NAME;
}

// Getter for Mac address
std::string Bot::getMacAddress() const {
    return this->MAC_ADDRESS;
}

// Getter for IP Addresses
std::vector<std::string> Bot::getIpAddresses() const {
    return this->IP_ADDRESSES;
}

// Setter for Device name
void Bot::setDeviceName(std::string newDeviceName) {
    this->DEVICE_NAME = newDeviceName;
}

// Setter for Mac Address
void Bot::setMacAddress(std::string newMacAddress) {
    this->MAC_ADDRESS = newMacAddress;
}

// Method to add new IP Address
void Bot::addIpAddress(std::string ipAddress) {
    this->IP_ADDRESSES.push_back(ipAddress);
}
