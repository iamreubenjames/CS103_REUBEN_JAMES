#pragma once

#define NOMINMAX
#include <iostream>
#include <limits>
#include <Windows.h> // For system calls; consider cross-platform alternatives
#include "json.hpp" // For JSON manipulation
#include "fileManagement.h" // Assumed to contain jsonDataFile function
#include "menus.h" // Assumed to contain applicationTitle and possibly validNumber

// Function Prototypes for better code organization
void adminMenu();
void customerScreen();
void adminCustomerReport();
void printAllClaims();
void applicationTitle();

// Admin feature: Display all customer reports
void adminCustomerReport() {
    auto userInfo = loadJsonDataFile(); // Load user data from a JSON file

    applicationTitle(); // Display the application title/header

    std::cout << "Customer Report Screen\n\n"
        << "Registered Customers: " << userInfo["user"].size() << "\n\n";

    for (const auto& item : userInfo["user"].items()) {
        const auto& user = item.value();
        std::cout << "\n" << user["userName"] << "\n"
            << "  Password: " << user["password"] << "\n"
            << "  Username: " << user["userName"] << "\n"
            << "  Full Name: " << user["fullName"] << "\n"
            << "  Email: " << user["email"] << "\n"
            << "  Vehicle Registration: " << user["vehicleRego"] << "\n";
    }

    system("pause");
    system("cls");
    adminMenu();
}

// Admin feature: Print all insurance claims
void printAllClaims() {
    auto jsonData = loadJsonDataFile(); // Load JSON data

    applicationTitle(); // Display the application title/header

    if (jsonData.contains("user")) {
        for (const auto& user : jsonData["user"].items()) {
            if (user.value().contains("claims")) {
                std::cout << "User: " << user.key() << "\n";
                for (const auto& claim : user.value()["claims"]) {
                    std::cout << "Policy Number: " << claim["PolicyNum"] << "\n"
                        << "Full Name: " << claim["FullName"] << "\n"
                        << "Date: " << claim["Date"] << "\n"
                        << "Time: " << claim["Time"] << "\n"
                        << "Incident Description: " << claim["IncidentDescription"] << "\n"
                        << "Complaint Details: " << claim["ComplaintDetails"] << "\n"
                        << std::string(50, '-') << "\n";
                }
            }
        }
    }
    else {
        std::cout << "\nNo claims found in the JSON.\n";
    }

    system("pause");
    system("cls");
    adminMenu();
}

// Admin menu function
void adminMenu() {
    applicationTitle();

    char userInput;

    std::cout << "Admin Menu\n\n"
        << "1. Customer Report\n"
        << "2. Weekly Claim Report\n"
        << "3. Weekly Registration Report\n"
        << "4. Return to Main Menu\n";

    std::cin >> userInput;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    switch (userInput) {
    case '1':
        Sleep(500);
        system("cls");
        adminCustomerReport();
        break;
    case '2':
        Sleep(500);
        system("cls");
        printAllClaims();
        break;
    case '3':
        // Placeholder for Weekly Registration Report functionality
        std::cout << "Feature not implemented yet.\n";
        Sleep(500);
        system("cls");
        break;
    case '4':
        Sleep(500);
        system("cls");
        customerScreen();
        break;
    default:
        std::cout << "\nIncorrect input. Please try again.\n";
        Sleep(500);
        system("cls");
        adminMenu();
    }
}
