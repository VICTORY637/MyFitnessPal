#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<User> userDatabase;

void displayMainMenu() {
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        std::cout << "Main Menu:\n";
        std::cout << "1. Log In\n";
        std::cout << "2. Sign In\n";
        std::cout << "3. Quit\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        switch (choice) {
        case 1:
            logIn();
            break;
        case 2:
            signIn();
            break;
        case 3:
            std::cout << "Exiting program. Goodbye!\n";
            exitProgram = true;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    }
}

void logIn() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    bool userFound = false;
    for (const auto& user : userDatabase) {
        if (user.username == username && user.password == password) {
            userFound = true;
            std::cout << "Welcome, " << username << "!\n";
            std::cout << "Your profile: \n";
            std::cout << "Age: " << user.age << "\n";
            std::cout << "Gender: " << user.gender << "\n";
            std::cout << "Height: " << user.height << "\n";
            std::cout << "Weight: " << user.weight << "\n";
            std::cout << "Goal: " << user.goal << "\n";
            break;
        }
    }

    if (!userFound) {
        std::cout << "Invalid username or password.\n";
    }
}

void signIn() {
    User newUser;
    std::cout << "Enter username: ";
    std::cin >> newUser.username;

    for (const auto& user : userDatabase) {
        if (user.username == newUser.username) {
            std::cout << "Username already exists. Please try a different one.\n";
            return;
        }
    }

    std::cout << "Enter password: ";
    std::cin >> newUser.password;

    // Age
    do {
        std::cout << "Enter age: ";
        if (!(std::cin >> newUser.age) || newUser.age < 0 || newUser.age > 120) {
            std::cout << "Invalid age. Please enter a number between 0 and 120.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else {
            break;
        }
    } while (true);

    // Gender
    do {
        std::cout << "Enter gender (M/F): ";
        std::cin >> newUser.gender;
        if (newUser.gender == 'm') newUser.gender = 'M';
        if (newUser.gender == 'f') newUser.gender = 'F';

        if (newUser.gender != 'M' && newUser.gender != 'F') {
            std::cout << "Invalid gender. Please enter M or F.\n";
        }
        else {
            break;
        }
    } while (true);

    // Height
    do {
        std::cout << "Enter height (cm): ";
        if (!(std::cin >> newUser.height) || newUser.height < 50 || newUser.height > 250) {
            std::cout << "Invalid height. Please enter a number between 50 and 250.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else {
            break;
        }
    } while (true);

    // Weight
    do {
        std::cout << "Enter weight (kg): ";
        if (!(std::cin >> newUser.weight) || newUser.weight < 15 || newUser.weight > 400) {
            std::cout << "Invalid weight. Please enter a number between 15 and 400.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else {
            break;
        }
    } while (true);

    // Aim
    do {
        std::cout << "Enter goal (\"L\" for LOSE / \"M\" for MAINTAIN / \"G\" for GAIN): ";
        std::cin >> newUser.goal;
        if (newUser.goal == "l") newUser.goal = "L";
        if (newUser.goal == "m") newUser.goal = "M";
        if (newUser.goal == "g") newUser.goal = "G";

        if (newUser.goal != "L" && newUser.goal != "M" && newUser.goal != "G") {
            std::cout << "Invalid goal. Please enter L, M or G.\n";
        }
        else {
            break;
        }
    } while (true);

    userDatabase.push_back(newUser);
    std::cout << "Account created successfully!\n";
}