// Bot.h

#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <string>
#include <vector>

class Bot {
private:
    std::string DEVICE_ID;
    std::string DEVICE_NAME;
    std::string MAC_ADDRESS;
    std::vector<std::string> IP_ADDRESSES;

public:
    // Default Constructor
    Bot();

    // Constructor
    Bot(std::string deviceId, std::string deviceName, std::string macAddress, std::vector<std::string> ipAddresses);

    // Getter for Device ID
    std::string getDeviceId() const;

    // Getter for Device Name
    std::string getDeviceName() const;

    // Getter for Mac address
    std::string getMacAddress() const;

    // Getter for IP Addresses
    std::vector<std::string> getIpAddresses() const;

    // Setter for Device name
    void setDeviceName(std::string newDeviceName);

    // Setter for Mac Address
    void setMacAddress(std::string newMacAddress);

    // Method to add new IP Address
    void addIpAddress(std::string ipAddress);
};

#endif // BOT_H
