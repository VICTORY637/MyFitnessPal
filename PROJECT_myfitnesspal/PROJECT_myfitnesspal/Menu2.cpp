#include "Menu2.h"
#include "User.logging.h"
#include "Calculations.h"


#include <iostream>


void editUserProfile(User& user) {
    int choice;
    bool done = false;

    while (!done) {
        std::cout << "\nEdit Profile:\n";
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
            std::cout << "Returning to previous menu.\n";
            done = true;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }
    //Calculations
    calculateCaloriesAndMacros(user);
    std::cout << "Account edited successfully!\n";
}




void displayMyAccountMenu(User& user) {
    int choice;
    bool goBack = false;


    while (!goBack) {
        std::cout << "\nMy Account:\n";
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
            editUserProfile(user);
            goBack = true;
            break;
        case 2:
            std::cout << "Change password selected. Exiting program for now.\n";
            goBack = true;
            break;
        case 3:
            std::cout << "Going back to the main menu.\n";
            goBack = true;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    }
}





void displayMenu2(User& user) {
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
            std::cout << "Option 1 selected. Exiting program for now.\n";
            exitProgram = true;
            break;
        case 2:
            std::cout << "Option 2 selected. Exiting program for now.\n";
            exitProgram = true;
            break;
        case 3:
            std::cout << "Option 3 selected. Exiting program for now.\n";
            exitProgram = true;
            break;
        case 4:
            displayMyAccountMenu(user);
            break;
        case 5:
            std::cout << "Logging out. Goodbye!\n";
            exitProgram = true;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
}