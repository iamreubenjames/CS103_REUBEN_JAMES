#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"

// Use PascalCase for struct names and camelCase for variable names.
struct ClaimData {
    int policyNumber;
    std::string fullName;
    std::string date;
    std::string time;
    std::string incidentDescription;
    std::string complaintDetails;
    std::string currentUser;
};

struct UserData {
    int userId;
    std::string password;
    std::string userName;
    std::string fullName;
    std::string email;
    std::string vehicleRego;
    bool role;
};

struct PolicyData {
    int policyNumber;
    std::string vehicleRego;
    std::string vehicleName;
    std::string vehicleModel;
    std::string currentUser;
    std::string insuranceType;
};

// Load JSON data from a file
nlohmann::json loadJsonDataFile() {
    std::ifstream file("./database.json");
    if (!file.is_open()) {
        std::cerr << "Error opening database.json. Returning an empty JSON object.\n";
        return {};
    }

    nlohmann::json jsonData;
    try {
        file >> jsonData;
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << ". Returning an empty JSON object.\n";
        file.close();
        return {};
    }

    file.close();
    return jsonData;
}

// Add a new user to the JSON database
void addNewUser(const UserData& newUser) {
    auto userDataJson = loadJsonDataFile();
    if (!userDataJson.contains("lastUserId")) {
        userDataJson["lastUserId"] = 0;
    }

    int newUserId = userDataJson["lastUserId"].get<int>() + 1;
    userDataJson["lastUserId"] = newUserId;

    // Simplified user data addition using a helper function
    auto& userJson = userDataJson["user"][newUser.userName];
    userJson = {
        {"userId", newUserId},
        {"password", newUser.password},
        {"userName", newUser.userName},
        {"fullName", newUser.fullName},
        {"email", newUser.email},
        {"vehicleRego", newUser.vehicleRego},
        {"role", newUser.role}
    };

    std::ofstream file("./database.json", std::ios::out);
    file << std::setw(4) << userDataJson;
    file.close();
}

// Add a new policy to the JSON database
void addNewPolicy(const PolicyData& newPolicy) {
    auto policyJson = loadJsonDataFile();

    if (!policyJson["user"].contains(newPolicy.currentUser)) {
        std::cout << "User not found in JSON. Unable to add policy.\n";
        return;
    }

    auto& userPolicies = policyJson["user"][newPolicy.currentUser]["policies"];
    if (userPolicies.is_null()) {
        userPolicies = nlohmann::json::array();
    }

    userPolicies.push_back({
        {"PolicyNumber", newPolicy.policyNumber},
        {"VehicleRego", newPolicy.vehicleRego},
        {"VehicleName", newPolicy.vehicleName},
        {"VehicleModel", newPolicy.vehicleModel},
        {"InsuranceType", newPolicy.insuranceType}
        });

    std::ofstream file("./database.json", std::ios::out);
    file << std::setw(4) << policyJson;
    file.close();
}

// Add a new claim to the JSON database
void saveClaimData(const ClaimData& claim) {
    auto claimJson = loadJsonDataFile();

    if (!claimJson["user"].contains(claim.currentUser)) {
        std::cout << "User not found in JSON. Unable to add claim.\n";
        return;
    }

    auto& userClaims = claimJson["user"][claim.currentUser]["claims"];
    if (userClaims.is_null()) {
        userClaims = nlohmann::json::array();
    }

    userClaims.push_back({
        {"PolicyNumber", claim.policyNumber},
        {"FullName", claim.fullName},
        {"Date", claim.date},
        {"Time", claim.time},
        {"IncidentDescription", claim.incidentDescription},
        {"ComplaintDetails", claim.complaintDetails}
        });

    std::ofstream file("./database.json", std::ios::out);
    file << std::setw(4) << claimJson;
    file.close();
}
