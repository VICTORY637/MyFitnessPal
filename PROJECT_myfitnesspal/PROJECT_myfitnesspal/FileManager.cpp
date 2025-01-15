#include "FileManager.h"
#include "User.logging.h"
#include <fstream>
#include <iostream>

const std::string userDatabaseFile = "users.txt";

void saveUsersToFile() {
    std::ofstream outFile(userDatabaseFile);
    if (!outFile) {
        std::cerr << "Error: Unable to save user data to file.\n";
        return;
    }

    for (const auto& user : userDatabase) {
        outFile << user.username << " "
            << user.password << " "
            << user.age << " "
            << user.gender << " "
            << user.height << " "
            << user.weight << " "
            << user.activity << " "
            << user.goal << " "
            << user.accountType << " "
            << user.dailyCalories << " "
            << user.protein << " "
            << user.fat << " "
            << user.carbs << "\n";
    }

    outFile.close();
    std::cout << "User data saved successfully.\n";
}

void loadUsersFromFile() {
    std::ifstream inFile(userDatabaseFile);
    if (!inFile) {
        std::cerr << "No user data file found. Starting fresh.\n";
        return;
    }

    User user;
    while (inFile >> user.username >> user.password >> user.age >> user.gender >> user.height >> user.weight
        >> user.activity >> user.goal >> user.accountType >> user.dailyCalories >> user.protein
        >> user.fat >> user.carbs) {
        userDatabase.push_back(user);
        std::cout << "Loaded user: " << user.username << "\n";
    }

    if (userDatabase.empty()) {
        std::cerr << "Warning: No users found in file.\n";
    }
    else {
        std::cout << "All users loaded successfully.\n";
    }

    inFile.close();
}

