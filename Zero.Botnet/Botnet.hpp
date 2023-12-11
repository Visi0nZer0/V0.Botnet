#ifndef BOTNET_H
#define BOTNET_H

#include <iostream>
#include <vector>
#include "Bot.hpp"

class Botnet {
private:
    std::vector<Bot> BOTS;

public:
    // Getter for Bots
    std::vector<Bot> getBots() const;

    // Get a specific Bot by ID
    Bot getBotById(const std::string& DEVICE_ID) const;

    // Add a new bot to the Botnet
    void addBot(Bot bot);

    // Remove bot from the Botnet
    void removeBot(std::string& DEVICE_ID);

    void listDevices() const;
};

#endif // BOTNET_H
