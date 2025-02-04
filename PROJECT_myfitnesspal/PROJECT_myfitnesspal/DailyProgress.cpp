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
* This file contains the definitions of the functions which are related to the daily progress
* - displaying, editing, deleating of progress for specific date
*/

#include "DailyProgress.h"
#include "User.h"
#include "Others.h"
#include "FileManager.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>



void displayDailyProgress(const DailyProgress& progress, const User& user) {
    std::cout << "\n+-------------------------------------------+\n";
    std::cout << "\nDAILY PROGRESS FOR " << progress.date << ":\n\n";

    double remainingCalories = bigger(0.0, user.dailyCalories - progress.calorieBalance);
    std::cout << "Calorie balance: " << progress.calorieBalance << "/" << user.dailyCalories
        << " kcal (" << remainingCalories << " remaining)\n";

    if (user.accountType == 'P') {
        double remainingProtein = bigger(0.0, user.protein - progress.proteinIntake);
        double remainingFat = bigger(0.0, user.fat - progress.fatIntake);
        double remainingCarbs = bigger(0.0, user.carbs - progress.carbsIntake);

        std::cout << "Protein intake: " << progress.proteinIntake << "/" << user.protein
            << " g (" << remainingProtein << " remaining)\n";
        std::cout << "Fat intake: " << progress.fatIntake << "/" << user.fat
            << " g (" << remainingFat << " remaining)\n";
        std::cout << "Carbs intake: " << progress.carbsIntake << "/" << user.carbs
            << " g (" << remainingCarbs << " remaining)\n";
    }

    std::cout << "\nWater cups: " << progress.waterCups << " ";
    for (int i = 0; i < progress.waterCups; ++i) {
        std::cout << "\\_/ ";
    }
    std::cout << "\n";

    std::cout << "\nMeals:\n";
    for (const auto& meal : progress.meals) {
        std::cout << "- " << meal.name << " (Calories: " << meal.calories << ")\n";
    }

    std::cout << "\nWorkouts:\n";
    for (const auto& workout : progress.workouts) {
        std::cout << "- " << workout.name << " (Calories burned: " << workout.caloriesBurned << ")\n";
    }

    std::cout << "\n+-------------------------------------------+\n";
}






void displayProgressForDate(const std::vector<DailyProgress>& progressData, const User& user, const std::string& date) {
    for (const auto& dp : progressData) {
        if (dp.date == date) {
            displayDailyProgress(dp, user);
            return;
        }
    }
    std::cout << "No data available for the selected date.\n";
}




void deleteProgressForDate(std::vector<DailyProgress>& progressData, DailyProgress& progress, const std::string& date, const std::string& username) {
    bool found = false;
    size_t i = 0;

    while (i < progressData.size()) {
        if (progressData[i].date == date) {
            progressData.erase(progressData.begin() + i); //progressData.begin() is not a simple pointer, but an iterator; erase() expects an iterator
            found = true;
        }
        else {
            ++i;
        }
    }

    if (found) {
        std::cout << "Data for the selected date has been deleted.\n";
        if (date == progress.date) {
            std::cout << "Clearing current progress for today.\n";
            progress = {};
            progress.date = date;
        }
        saveDailyProgress(progressData, username);
    }
    else {
        std::cout << "No data found for the selected date.\n";
    }
}







void editDailyProgress(DailyProgress& progress, const User& user) {
    int choice;
    bool done = false;
    std::string username = user.username;
    std::vector<DailyProgress> progressData = loadDailyProgress(username);

    while (!done) {
        std::cout << "\nEdit Daily Progress for " << progress.date << ":\n";
        choice = inputIntValidatedData("1. Add meal\n2. Remove meal\n3. Add workout\n4. Remove workout\n"
            "5. Add water\n6. Remove water\n7. Save and back\nChoose an option: ", 1, 7);

        switch (choice) {
        case 1:
            addMeal(user, progress);
            break;
        case 2:
            removeMeal(progress, user);
            break;
        case 3:
            addWorkout(progress);
            break;
        case 4:
            removeWorkout(progress);
            break;
        case 5:
            progress.waterCups += inputIntValidatedData("Enter number of water cups to add: ", 1, 20);
            break;
        case 6:
            removeWater(progress);
            break;
        case 7:
            done = true;
            continue;
        }
    }

    progressData.push_back(progress);
    saveDailyProgress(progressData, user.username);
}







// ADD AND REMOVE FUNCTIONS:

void addMeal(const User& user, DailyProgress& progress) {
    Meal meal;
    std::cout << "Enter meal name: ";
    std::cin.ignore();
    std::getline(std::cin, meal.name);

    if (user.accountType == 'S') {
        meal.calories = inputDoubleValidatedData("Enter calories for the meal: ", 0, 10000);
        progress.calorieBalance += meal.calories;
    }
    else if (user.accountType == 'P') {
        int choice = inputIntValidatedData("Do you want to:\n1. Add calories directly\n"
            "2. Add detailed macros (protein, fat, carbs)\nChoose an option: ", 1, 2);

        if (choice == 1) {
            meal.calories = inputDoubleValidatedData("Enter calories for the meal: ", 0, 10000);
            progress.calorieBalance += meal.calories;
        }
        else if (choice == 2) {
            meal.protein = inputDoubleValidatedData("Enter protein (grams): ", 0, 1000);
            meal.fat = inputDoubleValidatedData("Enter fat (grams): ", 0, 1000);
            meal.carbs = inputDoubleValidatedData("Enter carbs (grams): ", 0, 1000);

            const int kklPerGramProtein = 4;
            const int kklPerGramFat = 9;
            const int kklPerGramCarbs = 4;

            meal.calories = (meal.protein * kklPerGramProtein) +
                (meal.fat * kklPerGramFat) +
                (meal.carbs * kklPerGramCarbs);

            progress.calorieBalance += meal.calories;
            progress.proteinIntake += meal.protein;
            progress.fatIntake += meal.fat;
            progress.carbsIntake += meal.carbs;
        }
    }

    progress.meals.push_back(meal);
    std::cout << "Meal added successfully.\n";
}







void removeMeal(DailyProgress& progress, const User& user) {
    if (progress.meals.empty()) {
        std::cout << "\nNo meals to remove.\n";
        return;
    }

    else if (progress.meals.size() == 1) {
        std::cout << "\nThere is only one meal in the list: " << progress.meals[0].name << ".\n";
        int choice = inputIntValidatedData("Do you want to remove it? (1. Yes, 2. No): ", 1, 2);

        if (choice == 1) {
            const Meal& meal = progress.meals[0];
            progress.calorieBalance -= meal.calories;
            progress.proteinIntake -= meal.protein;
            progress.fatIntake -= meal.fat;
            progress.carbsIntake -= meal.carbs;

            progress.meals.erase(progress.meals.begin());
            std::cout << "Meal removed successfully.\n";
        }
        else {
            std::cout << "No meal was removed.\n";
        }
        return;
    }

    std::cout << "\nCurrent meals:\n";
    for (int i = 0; i < progress.meals.size(); ++i) {
        std::cout << i + 1 << ". " << progress.meals[i].name << "\n";
    }

    int index = inputIntValidatedData("Enter the number of the meal to remove: ", 1, progress.meals.size());

    const Meal& meal = progress.meals[index - 1];

    progress.calorieBalance -= meal.calories;
    progress.proteinIntake -= meal.protein;
    progress.fatIntake -= meal.fat;
    progress.carbsIntake -= meal.carbs;

    progress.meals.erase(progress.meals.begin() + index - 1);
    std::cout << "Meal removed successfully.\n";
}



void addWorkout(DailyProgress& progress) {
    Workout workout;
    std::cout << "Enter workout name: ";
    std::cin.ignore();
    std::getline(std::cin, workout.name);
    workout.caloriesBurned = inputDoubleValidatedData("Enter calories burned: ", 0, 10000);
    progress.calorieBalance -= workout.caloriesBurned;
    progress.workouts.push_back(workout);
    std::cout << "Workout added successfully.\n";
}

void removeWorkout(DailyProgress& progress) {
    if (progress.workouts.empty()) {
        std::cout << "\nNo workouts to remove.\n";
        return;
    }

    if (progress.workouts.size() == 1) {
        std::cout << "\nThere is only one workout in the list: " << progress.workouts[0].name << ".\n";
        int choice = inputIntValidatedData("Do you want to remove it? (1. Yes, 2. No): ", 1, 2);

        if (choice == 1) {
            const Workout& workout = progress.workouts[0];
            progress.calorieBalance += workout.caloriesBurned;
            progress.workouts.erase(progress.workouts.begin());
            std::cout << "Workout removed successfully.\n";
        }
        else {
            std::cout << "No workout was removed.\n";
        }
        return;
    }

    std::cout << "\nCurrent workouts:\n";
    for (int i = 0; i < progress.workouts.size(); ++i) {
        std::cout << i + 1 << ". " << progress.workouts[i].name << "\n";
    }

    int index = inputIntValidatedData("Enter the number of the workout to remove: ", 1, progress.workouts.size());

    const Workout& workout = progress.workouts[index - 1];
    progress.calorieBalance += workout.caloriesBurned;
    progress.workouts.erase(progress.workouts.begin() + index - 1);
    std::cout << "Workout removed successfully.\n";
}




void removeWater(DailyProgress& progress) {
    int choice;

    switch (progress.waterCups) {
    case 0:
        std::cout << "\nYou already have 0 cups.\n";
        break;

    case 1:
        std::cout << "\nThere is only one cup added.\n";
        choice = inputIntValidatedData("Do you want to remove it? (1. Yes, 2. No): ", 1, 2);

        if (choice == 1) {
            progress.waterCups = 0;
            std::cout << "Cups removed successfully.\n";
        }
        else {
            std::cout << "No cups were removed.\n";
        }
        break;

    default:
        int cupsToRemove = inputIntValidatedData("Enter number of water cups to remove: ", 1, progress.waterCups);
        progress.waterCups -= cupsToRemove;
        std::cout << "Cups removed successfully.\n";
        break;
    }
}