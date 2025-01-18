#include "Menu.h"
#include "User.h"
#include "FileManager.h"
#include "DailyProgress.h"
#include "Others.h"

#include <iostream>

void displayMyAccountMenu(User& user) {
    int choice;
    bool back = true;

    while (back) {
        std::cout << "\nMy Account:\n";
        printUserInformation(user);

        choice = inputIntValidatedData("\n1. Edit physical characteristics\n"
            "2. Edit user information\n3. Back\nChoose an option: ", 1, 3);

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



void displayHistoryMenu(User& user) {
        std::string filename = user.username;
        std::vector<DailyProgress> progressData = loadDailyProgress(filename);

        int choice;
        while (true) {
            choice = inputIntValidatedData("\nHistory Menu:\n1. View progress for a specific date\n"
                "2. Delete progress for a specific date\n"
                "3. Back to main menu\nChoose an option: ", 1, 3);
            if (choice == 1) { //View
                std::cin.ignore();
                std::string date;
                std::cout << "Enter the date (YYYY-MM-DD) to view progress: ";
                std::getline(std::cin, date);

                displayProgressForDate(progressData, user, date);
            }
            else if (choice == 2) { //Delete
                std::cin.ignore();
                std::string date;
                std::cout << "Enter the date (YYYY-MM-DD) to delete progress: ";
                std::getline(std::cin, date);

                deleteProgressForDate(progressData, date, user.username);
            }
            else if (choice == 3) { //Back
                break;
            }
            else {
                std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            }
        }
}





void displayMenu2(User& user, DailyProgress& currentProgress) {
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        choice = inputIntValidatedData("\nMY MENU:\n1. Progress for the day\n2. Edit current day data\n"
            "3. History\n4. My Account\n5. Logout\nChoose an option: ", 1, 5);

        switch (choice) {
        case 1: //Progress for the day
            displayDailyProgress(currentProgress, user);
            break;
        case 2: //Edit current day data
            editDailyProgress(currentProgress, user);
            break;
        case 3: {
            displayHistoryMenu(user);
            break;
        }
        case 4: //My Account
            displayMyAccountMenu(user);
            break;
        case 5: //Logout
            displayMainMenu();
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
}



void displayMainMenu()
{
    int choice;
    bool exitProgram = true;

    while (exitProgram)
    {
        choice = inputIntValidatedData("MAIN MENU:\n1. Log In\n2. Sign In\n"
            "3. Quit\nChoose an option: ", 1, 3);

        switch (choice)
        {
        case 1: {
            logIn();
            if (currentUser) return;
            break;
        }
        case 2: {
            signIn();
            break;
        }
        case 3: {
            std::cout << "\nGoodbye! Have a productive day!\n";
            exitProgram = false;
            exit(0);
            break;
        }
        default: {
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
        }
    }
}