#pragma once

#define NOMINMAX
#include <iostream>
#include <limits>
#include <string>
#include <Windows.h> // Consider conditional compilation or alternatives for cross-platform compatibility
#include "fileManagement.h"
#include "validation.h"
#include "admin.h"

// Function Declarations
void mainMenu();
void login();
void signUp();
void customerScreen();
void registerPolicy();
void applicationTitle();
void insurancePolicy();
int generateRandomPolicyNumber();

// Global variable to store the current user
std::string currentUser;
int loginAttempts = 3;

// Function Definitions
void login() {
    applicationTitle();
    std::string userName, password;

    std::cout << "Enter your username: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userName);

    std::cout << "\nEnter your password: ";
    std::getline(std::cin, password);

    if (validateLogin(userName, password)) {
        std::cout << "\nSign in successful.\n";
        currentUser = userName;
        Sleep(1000);
        system("cls");
        customerScreen();
    }
    else if (loginAttempts == 0) {
        std::cout << "\nFailed to login too many times. Please try again later.\n";
        Sleep(2000);
        system("cls");
        loginAttempts = 3;
        mainMenu();
    }
    else {
        loginAttempts--;
        std::cout << "\nInvalid login, try again.\n";
        Sleep(1000);
        system("cls");
        login();
    }
}

void signUp() {
    applicationTitle();
    UserData newUser; // Assuming UserData struct exists with userName, password, etc. as members
    std::string userInput;

    std::cout << "Enter your desired username: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userInput);
    newUser.userName = userInput;

    std::cout << "\nEnter your desired password: ";
    std::getline(std::cin, userInput);
    newUser.password = userInput;

    std::cout << "\nEnter your full name: ";
    std::getline(std::cin, userInput);
    newUser.fullName = userInput;

    do {
        std::cout << "\nEnter your email: ";
        std::getline(std::cin, userInput);
        if (!isValidEmail(userInput)) {
            std::cout << "\nThis is not a valid email.\n";
            Sleep(1000);
            system("cls");
        }
    } while (!isValidEmail(userInput));
    newUser.email = userInput;

    std::cout << "\nEnter your vehicle registration number: ";
    std::getline(std::cin, userInput);
    newUser.vehicleRego = userInput;

    newUser.role = false; // Assuming role is a bool indicating admin/user

    std::cout << "\nSign up successful.\n";
    addNewUser(newUser); // Assuming this function exists to add a user
    Sleep(1000);
    system("cls");
    mainMenu();
}

void insurancePolicy() {
    applicationTitle();

    std::cout << "Our Policies:\n\n";
    std::cout << "1. Third Party\nDescription: Covers losses caused by a third party.\nPrice: $200\n\n";
    std::cout << "2. Fire and Theft\nDescription: Covers losses caused by fire or theft.\nPrice: $150\n\n";
    std::cout << "3. Comprehensive\nDescription: Covers losses from accidental damage or from another individual.\nPrice: $250\n\n";
    std::cout << "Enter your choice (1-3) or press any other key to return: ";

    char userInput;
    std::cin >> userInput;

    switch (userInput) {
    case '1':
    case '2':
    case '3':
        Sleep(500);
        system("cls");
        registerPolicy(); // Assuming this function exists to handle policy registration
        break;
    default:
        Sleep(500);
        system("cls");
        customerScreen(); // Show customer screen again
        break;
    }
}

void applicationTitle() {
    std::cout << "-------------------------------------------------------------------------------------------------\n";
    std::cout << "                        NZ Vehicle Insurance System\n";
    std::cout << "-------------------------------------------------------------------------------------------------\n\n";
}


void registerPolicy() {
    PolicyData newUserPolicy;
    char userInput;

    applicationTitle();
    std::cout << "Thanks for choosing NZ Vehicle Insurance!\n"
        << "1. Register Third Party\n"
        << "2. Register Fire and Theft\n"
        << "3. Register Comprehensive\n"
        << "4. Return\n";


    bool validInput = false;
    do {

        std::cin >> userInput;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (userInput) {
        case '1':
            newUserPolicy.insuranceType = "Third Party";
            std::cout << "You chose our 'Third Party' Policy\n";
            break;
        case '2':
            newUserPolicy.insuranceType = "Fire and Theft";
            std::cout << "You chose our 'Fire and Theft' Policy\n";
            break;
        case '3':
            newUserPolicy.insuranceType = "Comprehensive";
            std::cout << "You chose our 'Comprehensive' Policy\n";
            break;
        case '4':
            Sleep(500);
            system("cls");
            customerScreen();
            return;
        default:
            std::cout << "Invalid input. Please try again.\n";
            break;
        }
    } while (!validInput);

    // Policy registration process
    newUserPolicy.policyNumber = generateRandomPolicyNumber();
    std::cout << "Your policy number is: " << newUserPolicy.policyNumber << "\n"
        << "Enter your vehicle registration number: ";
    std::getline(std::cin, newUserPolicy.vehicleRego);
    std::cout << "Enter your Vehicle's Model: ";
    std::getline(std::cin, newUserPolicy.vehicleModel);
    std::cout << "Enter your Vehicle's Name: ";
    std::getline(std::cin, newUserPolicy.vehicleName);

    newUserPolicy.currentUser = currentUser;

    std::cout << "Thanks for using NZ Vehicle Insurance, " << currentUser << "\n";
    addNewPolicy(newUserPolicy);
    Sleep(1000);
    system("cls");
    customerScreen();
}

// Main menu function
void mainMenu() {
    char userInput;

    applicationTitle();
    std::cout << "1. Login\n2. Signup\n3. Exit\n";

    std::cin >> userInput;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    switch (userInput) {
    case '1':
        system("cls");
        login();
        break;
    case '2':
        system("cls");
        signUp();
        break;
    case '3':
        exit(0);
    default:
        std::cout << "Incorrect input...\n";
        Sleep(500);
        system("cls");
        mainMenu();
        break;
    }
}

// Register a new claim for the user
void registerClaim() {
    ClaimData newClaim;
    applicationTitle();
    newClaim.currentUser = currentUser;

    std::cout << "Enter your policy number: ";
    std::cin >> newClaim.policyNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    std::cout << "\nEnter your full name: ";
    std::getline(std::cin, newClaim.fullName);
    std::cout << "Enter the date of the incident: ";
    std::getline(std::cin, newClaim.date);
    std::cout << "Enter the time of the incident: ";
    std::getline(std::cin, newClaim.time);
    std::cout << "Enter a description of the incident: ";
    std::getline(std::cin, newClaim.incidentDescription);
    std::cout << "Enter complaint details: ";
    std::getline(std::cin, newClaim.complaintDetails);

    saveClaimData(newClaim);

    std::cout << "\nClaim successfully registered!\n";
    Sleep(1000);
    system("cls");
    customerScreen();
}

// Customer screen function
void customerScreen() {
    applicationTitle();
    auto userInfo = loadJsonDataFile(); // Assuming a function to load user data
    char userInput;

    std::cout << "Welcome back, " << userInfo["user"][currentUser]["userName"] << "\n\n"
        << "1. Add a New Policy\n2. Make a Claim\n3. Sign Out\n";
    if (userInfo["user"][currentUser]["role"]) {
        std::cout << "4. Admin Menu\n";
    }

    std::cin >> userInput;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    switch (userInput) {
    case '1':
        Sleep(500);
        system("cls");
        insurancePolicy();
        break;
    case '2':
        Sleep(500);
        system("cls");
        registerClaim();
        break;
    case '3':
        std::cout << "Signing out...\n";
        Sleep(500);
        system("cls");
        mainMenu();
        break;
    case '4':
        if (userInfo["user"][currentUser]["role"]) {
            Sleep(500);
            system("cls");
            adminMenu(); // Assuming this function exists
        }
        else {
            std::cout << "Incorrect input...\n";
            Sleep(500);
            system("cls");
            customerScreen();
        }
        break;
    default:
        std::cout << "Incorrect input...\n";
        Sleep(500);
        system("cls");
        customerScreen();
        break;
    }
}