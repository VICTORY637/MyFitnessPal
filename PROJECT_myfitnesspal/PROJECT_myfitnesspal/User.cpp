/**
*
* Solution to course project #09
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author VIKTORIYA ILIYANOVA BAMBALOVA
* @idnumber 0MI0600473
* @compiler VC
*
* This file contains the definitions of the functions which are related to the logging in and signing in of the users
* as well as the visualizing and editing the user info
* as well as the definition of the random quote function
*/

#include "User.h"
#include "Calculations.h"
#include "Menu.h"
#include "Others.h"
#include "FileManager.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

User* currentUser = nullptr;
std::vector<User> userDatabase;



//lig in
void logIn() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    for (User& user : userDatabase) {
        if (user.username == username && user.password == password) {
            currentUser = &user;
            std::cout << ".....................";
            std::cout << "\n\nWelcome, " << username << "!\n";
            displayMotivationalQuote();
            return;
        }
    }

    std::cout << "Invalid username or password.\n\n";
}






//quotes
void displayMotivationalQuote() {
    const int QUOTE_COUNT = 15;
    const char* quotes[QUOTE_COUNT] = {
        "Believe in yourself and all that you are.",
        "The secret of getting ahead is getting started.",
        "Every journey begins with a single step.",
        "You do not have to be great to start, but you have to start to be great.",
        "Push yourself, because no one else is going to do it for you.",
        "Success is not the key to happiness. Happiness is the key to success.",
        "Hardships often prepare ordinary people for an extraordinary destiny.",
        "Do not watch the clock; do what it does. Keep going.",
        "Action is the foundational key to all success.",
        "You are never too old to set another goal or to dream a new dream.",
        "Do not limit your challenges. Challenge your limits.",
        "The future depends on what you do today.",
        "The only way to do great work is to love what you do.",
        "Dream big and dare to fail.",
        "What we achieve inwardly will change outer reality."
    };

    int randomIndex = std::time(nullptr) % QUOTE_COUNT;

    std::cout << "\nMotivational Quote of the day: " << quotes[randomIndex] << "\n\n";
}






//sign in
void signIn() {
    User newUser;

    newUser.username = getValidUsername(userDatabase);

    std::cout << "Enter password: ";
    std::cin >> newUser.password;

    //Age
    newUser.age = inputIntValidatedData("Enter age: ", 0, 120);

    // Gender
    const char validGenders[] = { 'M', 'F' };
    newUser.gender = inputCharValidatedData("Enter gender (M/F): ", validGenders, 2);

    // Height
    newUser.height = inputDoubleValidatedData("Enter height (cm): ", 50, 250);

    // Weight
    newUser.weight = inputDoubleValidatedData("Enter weight (kg): ", 15, 400);

    // Daily Activity
    newUser.activity = inputIntValidatedData("Rate your daily activity from 1 to 5: ", 1, 5);

    // Goal
    const char validGoals[] = {'L', 'M', 'G'};
    newUser.goal = inputCharValidatedData("Enter goal (\"L\" for LOSE / \"M\" for MAINTAIN / \"G\" for GAIN): ", validGoals, 3);

    // Account Type
    const char validAccountTypes[] = {'S', 'P'};
    newUser.accountType = inputCharValidatedData("Enter account type (\"S\" for Standard / \"P\" for Premium): ", validAccountTypes, 2);

    // Calculate daily needs
    calculateCaloriesAndMacros(newUser);

    userDatabase.push_back(newUser);
    saveUsersToFile();
    std::cout << "Account created successfully!\n\n";
}





std::string getValidUsername(const std::vector<User>& userDatabase) {
    std::string username;

    while (true) {
        std::cout << "Enter username /only letters, numbers, dot (.) and underscore (_)/: ";
        std::cin >> username;

        if (!isValidFileName(username)) {
            std::cerr << "Invalid username! Use only letters, numbers, dot (.) and underscore (_).\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        bool uniqueUsername = true;
        for (const auto& user : userDatabase) {
            if (user.username == username) {
                std::cout << "Username already exists. Please try a different one.\n";
                uniqueUsername = false;
                break;
            }
        }

        if (uniqueUsername) break;
    }

    return username;
}






//edit phisical characteristics
void editPhisicalCharacteristics(User& user) {
    int choice;
    bool done = false;

    while (!done) {
        choice = inputIntValidatedData("\nEdit Physical Characteristics:\n1. Edit Age\n2. Gender\n3. Edit height\n4. Edit Weight\n5. Edit activity index\n6. Edit goal\n7. Back\nChoose an option: ", 1, 7);

        switch (choice) {
        case 1: {
            //Age
            user.age = inputIntValidatedData("Enter age: ", 0, 120);
            break;
        }
        case 2: {
            // Gender
            const char validGenders[] = { 'M', 'F' };
            user.gender = inputCharValidatedData("Enter gender (M/F): ", validGenders, 2);
            break;
        }
        case 3: {
            // Height
            user.height = inputDoubleValidatedData("Enter height (cm): ", 50, 250);
            break;
        }
        case 4: {
            // Weight
            user.weight = inputDoubleValidatedData("Enter weight (kg): ", 15, 400);
            break;
        }
        case 5: {
            // Daily Activity
            user.activity = inputIntValidatedData("Rate your daily activity from 1 to 5: ", 1, 5);
            break;
        }
        case 6: {
            // Goal
            const char validGoals[] = { 'L', 'M', 'G' };
            user.goal = inputCharValidatedData("Enter goal (\"L\" for LOSE / \"M\" for MAINTAIN / \"G\" for GAIN): ", validGoals, 3);
            break;
        }
        case 7: {
            //Back
            done = true;
            break;
        }
        }
    }

    calculateCaloriesAndMacros(user);
    saveUsersToFile();

    std::cout << "Account edited successfully!\n";
}



//edit user information
void editUserInformation(User& user) {
    int choice;
    bool done = false;

    while (!done) {
        choice = inputIntValidatedData("\nEdit User Information :\n1. Change Username\n"
            "2. Change Password\n3. Change Account type\n4. Back\nChoose an option: ", 1, 4);

        switch (choice) {
        case 1: {
            std::cout << "Warning: Changing your username will delete your progress up to today.\n";
            int confirmation = inputIntValidatedData("Are you sure you want to continue ?\n1. yes\n2. no\n", 1, 2);
            if (confirmation == 1) {
                std::string newUsername;
                std::cout << "Enter new username: ";
                std::cin >> newUsername;

                bool usernameExists = false;
                for (const User& existingUser : userDatabase) {
                    if (existingUser.username == newUsername) {
                        usernameExists = true;
                        break;
                    }
                }

                if (usernameExists) {
                    std::cout << "Username already exists. Please try a different one.\n";
                }
                else {
                    user.username = newUsername;
                    std::cout << "Username updated successfully.\n";
                }
            }
            else break;
        }
        case 2: {
            std::string currentPassword, newPassword;

            std::cout << "Enter your current password: ";
            std::cin >> currentPassword;

            if (currentPassword != user.password) {
                std::cout << "Incorrect password. Try again.\n";
                break;
            }

            std::cout << "Enter new password: ";
            std::cin >> newPassword;

            user.password = newPassword;
            std::cout << "Password updated successfully.\n";
            break;
        }
        case 3: {
            const char validAccountTypes[] = { 'S', 'P' };
            user.accountType = inputCharValidatedData("Enter new account type (S for Standard, P for Premium): ", validAccountTypes, 2);
            break;
        }
        case 4: {
            done = true;
            break;
        }
        }
    }
    saveUsersToFile();
}





//print user information
void printUserInformation(const User& user) {
    std::cout << "Username: " << user.username << "\n";
    std::cout << (user.accountType == 'S' ? "STANDARD account\n" : "PREMIUM account\n");
    std::cout << "Age: " << user.age << "\n";
    std::cout << (user.gender == 'M' ? "Gender: male\n" : "Gender: female\n");
    std::cout << "Height: " << user.height << " cm\n";
    std::cout << "Weight: " << user.weight << " kg\n";
    std::cout << "Daily activity index: " << user.activity << "\n";
    std::cout << "Goal: " << (user.goal == 'L' ? "Lose" : (user.goal == 'M' ? "Maintain" : "Gain")) << "\n";
    std::cout << "Daily Calories: " << user.dailyCalories << " kcal\n";
    if (user.accountType == 'P') {
        std::cout << "Protein: " << user.protein << " g\n";
        std::cout << "Fat: " << user.fat << " g\n";
        std::cout << "Carbs: " << user.carbs << " g\n";
    }
}