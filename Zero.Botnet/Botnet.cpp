#include "Botnet.hpp"
#include <algorithm>

// Getter for Bots
std::vector<Bot> Botnet::getBots() const {
    return this->BOTS;
}

// Get a specific Bot by ID
Bot Botnet::getBotById(const std::string& DEVICE_ID) const {
    auto it = std::find_if(BOTS.begin(), BOTS.end(), [DEVICE_ID](const Bot& bot) {
        return bot.getDeviceId() == DEVICE_ID;
        });

    if (it != BOTS.end()) {
        return *it;
    }
    else {
        return Bot();
    }
}

// Add a new bot to the Botnet
void Botnet::addBot(Bot bot) {
    this->BOTS.push_back(bot);
}

// Remove bot from the Botnet
void Botnet::removeBot(std::string& DEVICE_ID) {
    BOTS.erase(
        std::remove_if(
            BOTS.begin(),
            BOTS.end(),
            [DEVICE_ID](const Bot& bot) { return bot.getDeviceId() == DEVICE_ID; }
        ),
        BOTS.end()
    );

    std::cout << "[-] Removed Bot[" << DEVICE_ID << "] from Botnet." << std::endl;
}

void Botnet::listDevices() const {
    int index = 0;
    for (const auto& bot : this->getBots()) {
        std::cout << "[" << index++ << "] " << bot.getDeviceId() << std::endl;
    }
}