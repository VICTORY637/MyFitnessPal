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
* This file contains the declarations of the functions which will be the MENUS
* (a description of the menu structure can be found in the file "Structure.plan.txt"
*/

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
        }
    }
}




void displayHistoryMenu(User& user, DailyProgress& progress) {
    std::string filename = user.username;
    std::vector<DailyProgress> progressData = loadDailyProgress(filename); //will contain all previous records of daily progress

    int choice;
    while (true) {
        choice = inputIntValidatedData("\nHISTORY MENU:\n1. View progress for a specific date\n"
            "2. Delete progress for a specific date\n"
            "3. Back\nChoose an option: ", 1, 3);

        switch (choice) {
        case 1: { // View
            std::cin.ignore();
            std::string date;
            std::cout << "Enter the date (YYYY-MM-DD) to view progress: ";
            std::getline(std::cin, date);

            displayProgressForDate(progressData, user, date);
            break;
        }
        case 2: { // Delete
            std::cin.ignore();
            std::string date;
            std::cout << "Enter the date (YYYY-MM-DD) to delete progress: ";
            std::getline(std::cin, date);

            deleteProgressForDate(progressData, progress, date, user.username);
            break;
        }
        case 3: { // Back
            return;
        }
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
        case 1: {//Progress for the day
            displayDailyProgress(currentProgress, user);
            break;
        }
        case 2: {//Edit current day data
            editDailyProgress(currentProgress, user);
            break;
        }
        case 3: {
            displayHistoryMenu(user, currentProgress);
            break;
        }
        case 4: { //My Account
            displayMyAccountMenu(user);
            break;
        }
        case 5: { //Logout
            exitProgram = true;
            displayMainMenu();
            break;
        }
        }
    }
}




bool displayMainMenu() {
    int choice;

    while (true) {
        choice = inputIntValidatedData("\nMAIN MENU : \n1. Log In\n2. Sign In\n"
            "3. Quit\nChoose an option: ", 1, 3);

        switch (choice) {
        case 1:
            logIn();
            if (currentUser) return true;
            break;
        case 2:
            signIn();
            break;
        case 3:
            std::cout << "\nGoodbye! Have a productive day!\n";
            exit(0);
        }
    }
}
