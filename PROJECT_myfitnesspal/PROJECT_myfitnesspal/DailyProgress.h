#ifndef DAILY_PROGRESS_H
#define DAILY_PROGRESS_H

#include <string>
#include <vector>
#include "User.h"

struct Meal {
    std::string name = "";
    double calories = 0.0;
    double protein = 0.0;
    double fat = 0.0;
    double carbs = 0.0;
};

struct Workout {
    std::string name;
    double caloriesBurned;
};

struct DailyProgress {
    std::string date = "";
    double calorieBalance = 0.0;
    double proteinIntake = 0.0;
    double fatIntake = 0.0;
    double carbsIntake = 0.0;
    int waterCups = 0;
    std::vector<Meal> meals;
    std::vector<Workout> workouts;
};

void displayProgressForDate(const std::vector<DailyProgress>& progressData, const User& user, const std::string& date);
//void deleteProgressForDate(std::vector<DailyProgress>& progressData, const std::string& date);
void deleteProgressForDate(std::vector<DailyProgress>& progressData, const std::string& date, const std::string& username);

void displayDailyProgress(const DailyProgress& progress, const User& user);
void editDailyProgress(DailyProgress& progress, const User& user);

void addMeal(const User& user, DailyProgress& progress);
void removeMeal(DailyProgress& progress, const User& user);
void addWorkout(DailyProgress& progress);
void removeWorkout(DailyProgress& progress);

#endif