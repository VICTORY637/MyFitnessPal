#include "DailyProgress.h"
#include "User.logging.h"
#include <iostream>
#include <fstream>

//void saveDailyProgress(const std::vector<DailyProgress>& progressData, const std::string& filename) {
//    std::ofstream outFile(filename, std::ios::trunc);
//    if (!outFile) {
//        std::cerr << "Error: Unable to save daily progress data to file.\n";
//        return;
//    }
//
//    for (const auto& progress : progressData) {
//        outFile << progress.date << "\n";
//        outFile << progress.calorieBalance << "\n";
//        outFile << progress.proteinIntake << "\n";
//        outFile << progress.fatIntake << "\n";
//        outFile << progress.carbsIntake << "\n";
//        outFile << progress.waterCups << "\n";
//
//        outFile << progress.meals.size() << "\n";
//        for (const auto& meal : progress.meals) {
//            outFile << meal << "\n";
//        }
//
//        outFile << progress.workouts.size() << "\n";
//        for (const auto& workout : progress.workouts) {
//            outFile << workout << "\n";
//        }
//    }
//
//    outFile.close();
//    std::cout << "Daily progress data saved successfully.\n";
//}

void saveDailyProgress(const std::vector<DailyProgress>& progressData, const std::string& username) {
    std::string filename = "progress_" + username + ".txt";
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error: Unable to save daily progress data to file.\n";
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
            outFile << meal << "\n";
        }

        outFile << progress.workouts.size() << "\n";
        for (const auto& workout : progress.workouts) {
            outFile << workout << "\n";
        }
    }

    outFile.close();
    std::cout << "Daily progress data for " << username << " saved successfully.\n";
}


//std::vector<DailyProgress> loadDailyProgress(const std::string& filename) {
//    std::ifstream inFile(filename);
//    if (!inFile) {
//        std::cerr << "No daily progress data file found. Starting fresh.\n";
//        return {};
//    }
//
//    std::vector<DailyProgress> progressData;
//    DailyProgress progress;
//
//    while (std::getline(inFile, progress.date)) {
//        inFile >> progress.calorieBalance;
//        inFile >> progress.proteinIntake;
//        inFile >> progress.fatIntake;
//        inFile >> progress.carbsIntake;
//        inFile >> progress.waterCups;
//
//        int mealsCount;
//        inFile >> mealsCount;
//        inFile.ignore();
//        progress.meals.clear();
//        for (int i = 0; i < mealsCount; ++i) {
//            std::string meal;
//            std::getline(inFile, meal);
//            progress.meals.push_back(meal);
//        }
//
//        int workoutsCount;
//        inFile >> workoutsCount;
//        inFile.ignore();
//        progress.workouts.clear();
//        for (int i = 0; i < workoutsCount; ++i) {
//            std::string workout;
//            std::getline(inFile, workout);
//            progress.workouts.push_back(workout);
//        }
//
//        progressData.push_back(progress);
//    }
//
//    inFile.close();
//    return progressData;
//}


std::vector<DailyProgress> loadDailyProgress(const std::string& username) {
    std::string filename = "progress_" + username + ".txt";
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "No progress data file found for " << username << ". Starting fresh.\n";
        return {};
    }

    std::vector<DailyProgress> progressData;
    DailyProgress progress;

    while (std::getline(inFile, progress.date)) {
        inFile >> progress.calorieBalance;
        inFile >> progress.proteinIntake;
        inFile >> progress.fatIntake;
        inFile >> progress.carbsIntake;
        inFile >> progress.waterCups;

        int mealsCount;
        inFile >> mealsCount;
        inFile.ignore();
        progress.meals.clear();
        for (int i = 0; i < mealsCount; ++i) {
            std::string meal;
            std::getline(inFile, meal);
            progress.meals.push_back(meal);
        }

        int workoutsCount;
        inFile >> workoutsCount;
        inFile.ignore();
        progress.workouts.clear();
        for (int i = 0; i < workoutsCount; ++i) {
            std::string workout;
            std::getline(inFile, workout);
            progress.workouts.push_back(workout);
        }

        progressData.push_back(progress);
    }

    inFile.close();
    return progressData;
}


void displayDailyProgress(const DailyProgress& progress, const User& user) {
    std::cout << "\nDaily Progress for " << progress.date << ":\n";

    if (user.accountType == 'P') {
        std::cout << "Calorie balance: " << progress.calorieBalance << "/" << user.dailyCalories << " kcal\n";
        std::cout << "Protein intake: " << progress.proteinIntake << "/" << user.protein << " g\n";
        std::cout << "Fat intake: " << progress.fatIntake << "/" << user.fat << " g\n";
        std::cout << "Carbs intake: " << progress.carbsIntake << "/" << user.carbs << " g\n";
    }
    else {
        std::cout << "Calorie balance: " << progress.calorieBalance << "/" << user.dailyCalories << " kcal\n";
    }

    std::cout << "Water cups: " << progress.waterCups << "\n";

    std::cout << "\nMeals:\n";
    for (const auto& meal : progress.meals) {
        std::cout << "- " << meal << "\n";
    }

    std::cout << "\nWorkouts:\n";
    for (const auto& workout : progress.workouts) {
        std::cout << "- " << workout << "\n";
    }
}

void editDailyProgress(DailyProgress& progress, const User& user) {
    int choice;
    bool done = false;

    while (!done) {
        std::cout << "\nEdit Daily Progress for " << progress.date << ":\n";
        std::cout << "1. Add meal\n";
        std::cout << "2. Remove meal\n";
        std::cout << "3. Add workout\n";
        std::cout << "4. Remove workout\n";
        std::cout << "5. Add water\n";
        std::cout << "6. Remove water\n";
        std::cout << "7. Back\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            std::string meal;
            std::cout << "Enter meal: ";
            std::cin.ignore();
            std::getline(std::cin, meal);

            double calories = 0.0, protein = 0.0, fat = 0.0, carbs = 0.0;
            if (user.accountType == 'P') {
                std::cout << "Enter calories: ";
                std::cin >> calories;
                std::cout << "Enter protein (grams): ";
                std::cin >> protein;
                std::cout << "Enter fat (grams): ";
                std::cin >> fat;
                std::cout << "Enter carbs (grams): ";
                std::cin >> carbs;

                progress.calorieBalance += calories;
                progress.proteinIntake += protein;
                progress.fatIntake += fat;
                progress.carbsIntake += carbs;
            }
            else {
                std::cout << "Enter calories: ";
                std::cin >> calories;
                progress.calorieBalance += calories;
            }

            progress.meals.push_back(meal);
            break;
        }
        case 2: {
            if (progress.meals.empty()) {
                std::cout << "No meals to remove.\n";
                break;
            }
            std::cout << "\nCurrent meals:\n";
            for (size_t i = 0; i < progress.meals.size(); ++i) {
                std::cout << i + 1 << ". " << progress.meals[i] << "\n";
            }
            std::cout << "Enter the number of the meal to remove: ";
            size_t index;
            std::cin >> index;
            if (index > 0 && index <= progress.meals.size()) {
                progress.meals.erase(progress.meals.begin() + index - 1);
            }
            else {
                std::cout << "Invalid index.\n";
            }
            break;
        }
        case 3: {
            std::string workout;
            std::cout << "Enter workout: ";
            std::cin.ignore();
            std::getline(std::cin, workout);
            progress.workouts.push_back(workout);
            break;
        }
        case 4: {
            if (progress.workouts.empty()) {
                std::cout << "No workouts to remove.\n";
                break;
            }
            std::cout << "\nCurrent workouts:\n";
            for (size_t i = 0; i < progress.workouts.size(); ++i) {
                std::cout << i + 1 << ". " << progress.workouts[i] << "\n";
            }
            std::cout << "Enter the number of the workout to remove: ";
            size_t index;
            std::cin >> index;
            if (index > 0 && index <= progress.workouts.size()) {
                progress.workouts.erase(progress.workouts.begin() + index - 1);
            }
            else {
                std::cout << "Invalid index.\n";
            }
            break;
        }
        case 5: {
            int waterToAdd;
            std::cout << "Enter number of water cups to add: ";
            std::cin >> waterToAdd;
            progress.waterCups += waterToAdd;
            break;
        }
        case 6: {
            int waterToRemove;
            std::cout << "Enter number of water cups to remove: ";
            std::cin >> waterToRemove;
            if (waterToRemove > progress.waterCups) {
                std::cout << "Not enough water cups to remove.\n";
            }
            else {
                progress.waterCups -= waterToRemove;
            }
            break;
        }
        case 7:
            done = true;
            break;
        default:
            std::cout << "Invalid input. Please enter a number between 1 and 7.\n";
        }
    }
}
