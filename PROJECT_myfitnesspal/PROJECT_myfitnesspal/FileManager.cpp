#include "FileManager.h"
#include "User.h"
#include <fstream>
#include <iostream>

//here are functions:
// saveDatabaseFile()
//loadUsersFromFile()

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
            << user.accountType << "\n";
    }

    std::cout << "User data saved successfully.\n"; // Debug message
    outFile.close();
}

void loadUsersFromFile() {
    std::ifstream inFile(userDatabaseFile);
    if (!inFile) {
        std::cerr << "No user data file found. Starting fresh.\n";
        return;
    }

    User user;
    while (inFile >> user.username >> user.password >> user.age >> user.gender >> user.height >> user.weight >> user.activity >> user.goal >> user.accountType) {
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
