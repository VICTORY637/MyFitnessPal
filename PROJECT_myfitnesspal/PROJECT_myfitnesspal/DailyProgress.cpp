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

    std::cout << "Water cups: " << progress.waterCups << " ";
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



void deleteProgressForDate(std::vector<DailyProgress>& progressData, const std::string& date, const std::string& username) {
    bool found = false;

    for (auto i = progressData.begin(); i != progressData.end(); ) {
        if ((*i).date == date) {
            i = progressData.erase(i);
            found = true;
        }
        else {
            ++i;
        }
    }

    if (found) {
        std::cout << "Data for the selected date has been deleted.\n";
        saveDailyProgress(progressData, username);
    }
    else {
        std::cout << "No data found for the selected date.\n";
    }
}




void editDailyProgress(DailyProgress& progress, const User& user) {
    int choice;
    bool done = false;
    std::string filename = "progress_" + user.username + ".txt";
    std::vector<DailyProgress> progressData = loadDailyProgress(filename);

    while (!done) {
        std::cout << "\nEdit Daily Progress for " << progress.date << ":\n";
        choice = inputIntValidatedData("1. Add meal\n2. Remove meal\n3. Add workout\n4. Remove workout\n"
            "5. Add water\n6. Remove water\n7. Back\nChoose an option: ", 1, 7);

        switch (choice) {
        case 1: {
            addMeal(user, progress);
            break;
        }
        case 2: {
            removeMeal(progress, user);
            break;
        }
        case 3: {
            addWorkout(progress);
            break;
        }
        case 4: {
            removeWorkout(progress);
            break;
        }
        case 5: {
            progress.waterCups += inputIntValidatedData("Enter number of water cups to add: ", 0, 30);
            break;
        }
        case 6: {
            if (progress.waterCups > 0) {
                progress.waterCups -= inputIntValidatedData("Enter number of water cups to remove: ", 0, progress.waterCups);
                break;
            }
            std::cout << "You already have 0 cups.\n";
            break;
        }
        case 7:
            done = true;
            break;
        default:
            std::cout << "Invalid input. Please enter a number between 1 and 7.\n";
        }
    }

    bool updated = false;
    for (auto& day : progressData) {
        if (day.date == progress.date) {
            day = progress;
            updated = true;
            break;
        }
    }

    if (!updated) {
        progressData.push_back(progress);
    }

    saveDailyProgress(progressData, user.username);
}








void addMeal(const User& user, DailyProgress& progress) {
    Meal meal;
    std::cout << "Enter meal name: ";
    std::cin.ignore();
    std::getline(std::cin, meal.name);

    if (user.accountType == 'S') {
        progress.calorieBalance += inputIntValidatedData("Enter calories for the meal: ", 0, 10000);
    }
    else if (user.accountType == 'P') {
        int choice = inputIntValidatedData("Do you want to:\n1. Add calories directly\n"
            "2. Add detailed macros (protein, fat, carbs)\nChoose an option: ", 1, 2);

        if (choice == 1) {
            progress.calorieBalance += inputIntValidatedData("Enter calories for the meal: ", 0, 10000);
        }
        else if (choice == 2) {
            meal.protein = inputIntValidatedData("Enter protein (grams): ", 0, 1000);
            meal.fat = inputIntValidatedData("Enter fat (grams): ", 0, 1000);
            meal.carbs = inputIntValidatedData("Enter carbs (grams): ", 0, 1000);
            
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
        std::cout << "No meals to remove.\n";
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
    workout.caloriesBurned = inputIntValidatedData("Enter calories burned: ", 0, 10000);
    progress.calorieBalance -= workout.caloriesBurned;
    progress.workouts.push_back(workout);
    std::cout << "Workout added successfully.\n";
}

void removeWorkout(DailyProgress& progress) {
    if (progress.workouts.empty()) {
        std::cout << "No workouts to remove.\n";
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
