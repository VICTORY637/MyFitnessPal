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
* This file contains the definitions of the functions which operating wiyh files,
* keeping the user account information and the progress of the user for a specific date,
* as well as the initializing of the string type constant, which will be the name of the file with users
*/

#include "FileManager.h"
#include "User.h"
#include "DailyProgress.h"

#include <fstream>
#include <iostream>

const std::string userDatabaseFile = "users.txt"; //global string varr for the file with users (outfile)

void saveUsersToFile() {
    std::ofstream outFile(userDatabaseFile); //create and open an outFile object of class std::ofstream to write the users data
    // file exists -> it will be cleaned; not -> will be created
    if (!outFile) { //check if the file is opened
        std::cout << "Error: Unable to save user data to file.\n";
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

    outFile.close(); //cloze the file
}










void loadUsersFromFile() {
    std::ifstream inFile(userDatabaseFile);
    if (!inFile) {
        //std::cout << "No user data file found.\n";
        //gorniqt komentar e za ulesnenie pri test :)
        return;
    }

    User user;
    while (inFile >> user.username >> user.password >> user.age >> user.gender >> user.height >> user.weight
        >> user.activity >> user.goal >> user.accountType >> user.dailyCalories >> user.protein
        >> user.fat >> user.carbs) {
        userDatabase.push_back(user);
        //::cout << "Loaded user: " << user.username << "\n";
        //gorniqt komentar e za ulesnenie pri test :)
    }

    /*if (userDatabase.empty()) {
        std::cout << "Warning: No users found in file.\n";
    }
    else {
        std::cout << "All users loaded successfully.\n";
    }*/
    //gorniqt komentar e za ulesnenie pri test :)

    inFile.close();
}








void saveDailyProgress(const std::vector<DailyProgress>& progressData, const std::string& username) {
    std::string filename = "progress_" + username + ".txt";
    std::ofstream outFile(filename, std::ios::trunc);

    if (!outFile) {
        std::cout << "Error: Unable to open file for writing: " << filename << "\n";
        return;
    }

    if (progressData.empty()) {
        return;
    }

    for (const auto& progress : progressData) {
        outFile << progress.date << "\n";
        outFile << progress.calorieBalance << "\n";
        outFile << progress.proteinIntake << "\n";
        outFile << progress.fatIntake << "\n";
        outFile << progress.carbsIntake << "\n";
        outFile << progress.waterCups << "\n";

        outFile << progress.meals.size() << "\n";
        for (const auto& meal : progress.meals) {
            outFile << meal.name << "\n";
            outFile << meal.calories << "\n";
            outFile << meal.protein << "\n";
            outFile << meal.fat << "\n";
            outFile << meal.carbs << "\n";
        }

        outFile << progress.workouts.size() << "\n";
        for (const auto& workout : progress.workouts) {
            outFile << workout.name << "\n";
            outFile << workout.caloriesBurned << "\n";
        }
    }

    outFile.close();
}










std::vector<DailyProgress> loadDailyProgress(const std::string& username) {
    std::string filename = "progress_" + username + ".txt";
    std::ifstream inFile(filename);

    if (!inFile) {
        return {};
    }

    std::vector<DailyProgress> progressData;

    while (true) {
        DailyProgress progress;

        if (!std::getline(inFile, progress.date)) break; // read fails if (the file is empty or the format is wrong)
        if (!(inFile >> progress.calorieBalance >> progress.proteinIntake
            >> progress.fatIntake >> progress.carbsIntake >> progress.waterCups)) {
            break;
        }
        inFile.ignore();

        int mealsCount;
        if (!(inFile >> mealsCount)) break;
        inFile.ignore();
        progress.meals.clear();

        for (int i = 0; i < mealsCount; ++i) {
            Meal meal;
            if (!std::getline(inFile, meal.name) || !(inFile >> meal.calories >> meal.protein >> meal.fat >> meal.carbs)) {
                break;
            }
            inFile.ignore();
            progress.meals.push_back(meal);
        }

        int workoutsCount;
        if (!(inFile >> workoutsCount)) break;
        inFile.ignore();
        progress.workouts.clear();

        for (int i = 0; i < workoutsCount; ++i) {
            Workout workout;
            if (!std::getline(inFile, workout.name) || !(inFile >> workout.caloriesBurned)) {
                break;
            }
            inFile.ignore();
            progress.workouts.push_back(workout);
        }

        progressData.push_back(progress);
    }

    inFile.close();

    /*if (progressData.empty()) {
        std::cout << "Warning: No valid progress data found in " << filename << ".\n";
    }*/

    return progressData;
}