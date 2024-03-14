#pragma once

#include <iostream>
#include <string>
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()
#include "fileManagement.h"
#include "json.hpp"

// Generate a random policy number
int generateRandomPolicyNumber() {
    srand(static_cast<unsigned>(time(nullptr)));
    int number = 1000 + (rand() % 50000);
    return number;
}

// Validate email format
bool isValidEmail(const std::string& userEmail) {
    return userEmail.find('@') != std::string::npos && userEmail.find('.') != std::string::npos;
}

// Validate if user input is a number within a specified range
bool isValidNumber(char lowerBound, char upperBound, char userInput) {
    if (!isdigit(userInput)) {
        return false;
    }

    int userNum = userInput - '0';
    int lowerNum = lowerBound - '0';
    int upperNum = upperBound - '0';

    return userNum >= lowerNum && userNum <= upperNum;
}

// Validate login credentials
bool validateLogin(const std::string& userName, const std::string& password) {
    nlohmann::json data = loadJsonDataFile(); // Assuming jsonDataFile is renamed to loadJsonDataFile for clarity
    bool userExists = data["user"].contains(userName);

    if (!userExists) {
        std::cout << "Invalid Username or Password" << std::endl;
        return false;
    }

    return data["user"][userName]["password"] == password;
}
