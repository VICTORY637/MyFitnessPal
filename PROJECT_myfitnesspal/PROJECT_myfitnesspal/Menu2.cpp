#include "Menu2.h"
#include "User.logging.h"
#include "Calculations.h"
#include "DailyProgress.h"
#include <iostream>

void editPhisicalCharacteristics(User& user) {
    int choice;
    bool done = false;

    while (!done) {
        std::cout << "\nEdit Physical Characteristics:\n";
        std::cout << "1. Edit Age\n";
        std::cout << "2. Edit Weight\n";
        std::cout << "3. Edit Goal\n";
        std::cout << "4. Edit Gender\n";
        std::cout << "5. Edit Account Type\n";
        std::cout << "6. Back\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        switch (choice) {
        case 1:
            std::cout << "Enter new age: ";
            std::cin >> user.age;
            break;
        case 2:
            std::cout << "Enter new weight: ";
            std::cin >> user.weight;
            break;
        case 3:
            std::cout << "Enter new goal (L for Lose, M for Maintain, G for Gain): ";
            std::cin >> user.goal;
            if (user.goal == 'l') user.goal = 'L';
            if (user.goal == 'm') user.goal = 'M';
            if (user.goal == 'g') user.goal = 'G';
            break;
        case 4:
            std::cout << "Enter new gender (M for Male, F for Female): ";
            std::cin >> user.gender;
            if (user.gender == 'm') user.gender = 'M';
            if (user.gender == 'f') user.gender = 'F';
            break;
        case 5:
            std::cout << "Enter new account type (S for Standard, P for Premium): ";
            std::cin >> user.accountType;
            if (user.accountType == 's') user.accountType = 'S';
            if (user.accountType == 'p') user.accountType = 'P';
            break;
        case 6:
            done = true;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }

    calculateCaloriesAndMacros(user);
    std::cout << "Account edited successfully!\n";
}

void editUserInformation(User& user) {
    int choice;
    bool done = false;

    while (!done) {
        std::cout << "\nEdit User Information:\n";
        std::cout << "1. Change Username\n";
        std::cout << "2. Change Password\n";
        std::cout << "3. Back\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            std::string newUsername;
            std::cout << "Enter new username: ";
            std::cin >> newUsername;

            bool usernameExists = false;
            for (const auto& existingUser : userDatabase) {
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
            break;
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
        case 3:
            done = true;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    }
}

void displayMyAccountMenu(User& user) {
    int choice;
    bool back = true;

    while (back) {
        std::cout << "\nMy Account:\n";
        printUserInformation(user);
        std::cout << "1. Edit physical characteristics\n";
        std::cout << "2. Edit user information\n";
        std::cout << "3. Back\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        switch (choice) {
        case 1:
            editPhisicalCharacteristics(user);
            break;
        case 2:
            editUserInformation(user);
            break;
        case 3:
            back = false;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    }
}

void displayMenu2(User& user, DailyProgress& currentProgress) {
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        std::cout << "\nMenu 2:\n";
        std::cout << "1. Progress for the day\n";
        std::cout << "2. Edit current day data\n";
        std::cout << "3. History\n";
        std::cout << "4. My Account\n";
        std::cout << "5. Logout\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
        case 1:
            displayDailyProgress(currentProgress, user);
            break;
        case 2:
            editDailyProgress(currentProgress, user);
            break;
        case 3:
            // History functionality can be implemented here
            break;
        case 4:
            displayMyAccountMenu(user);
            break;
        case 5:
            exitProgram = true;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
}

void printUserInformation(const User& user) {
    std::cout << "Username: " << user.username << "\n";
    std::cout << (user.accountType == 'S' ? "STANDARD account\n" : "PREMIUM account\n");
    std::cout << "Age: " << user.age << "\n";
    std::cout << (user.gender == 'M' ? "Gender: male\n" : "Gender: female\n");
    std::cout << "Height: " << user.height << " cm\n";
    std::cout << "Weight: " << user.weight << " kg\n";
    std::cout << "Daily activity index: " << user.activity << "\n";
    std::cout << "Goal: " << (user.goal == 'L' ? "Lose" : user.goal == 'M' ? "Maintain" : "Gain") << "\n";
    std::cout << "Daily Calories: " << user.dailyCalories << " kcal\n";
    if (user.accountType == 'P') {
        std::cout << "Protein: " << user.protein << " g\n";
        std::cout << "Fat: " << user.fat << " g\n";
        std::cout << "Carbs: " << user.carbs << " g\n";
    }
}
