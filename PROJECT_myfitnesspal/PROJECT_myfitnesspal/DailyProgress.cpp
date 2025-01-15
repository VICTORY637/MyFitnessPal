#include "DailyProgress.h"
#include <iostream>
#include <fstream>

void saveDailyProgress(const std::vector<DailyProgress>& progressData, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error: Unable to save daily progress data to file.\n";
        return;
    }

    for (const auto& progress : progressData) {
        outFile << progress.date << "\n";
        outFile << progress.calorieBalance << "\n";
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
    std::cout << "Daily progress data saved successfully.\n";
}


std::vector<DailyProgress> loadDailyProgress(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "No daily progress data file found. Starting fresh.\n";
        return {};
    }

    std::vector<DailyProgress> progressData;
    DailyProgress progress;

    while (std::getline(inFile, progress.date)) {
        inFile >> progress.calorieBalance;
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


void displayDailyProgress(const DailyProgress& progress) {
    std::cout << "\nDaily Progress for " << progress.date << ":\n";
    std::cout << "Calorie balance: " << progress.calorieBalance << " kcal\n";
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


void editDailyProgress(DailyProgress& progress) {
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
            progress.meals.push_back(meal);
            break;
        }
        case 2: {
            if (progress.meals.empty()) {
                std::cout << "No meals to remove.\n";
                break;
            }
            std::cout << "Enter the number of the meal to remove: ";
            size_t index;
            std::cin >> index;
            if (index > 0 && index <= progress.meals.size()) {
                progress.meals.erase(progress.meals.begin() + index - 1);
                std::cout << "Meal removed successfully.\n";
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
            std::cout << "Enter the number of the workout to remove: ";
            size_t index;
            std::cin >> index;
            if (index > 0 && index <= progress.workouts.size()) {
                progress.workouts.erase(progress.workouts.begin() + index - 1);
                std::cout << "Workout removed successfully.\n";
            }
            else {
                std::cout << "Invalid index.\n";
            }
            break;
        }
        case 5:
            int waterToAdd;
            std::cout << "Enter number of water cups to add: ";
            std::cin >> waterToAdd;
            progress.waterCups += waterToAdd;
            break;
        case 6:
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
        case 7:
            done = true;
            break;
        default:
            std::cout << "Invalid input. Please enter a number between 1 and 7.\n";
        }
    }
}