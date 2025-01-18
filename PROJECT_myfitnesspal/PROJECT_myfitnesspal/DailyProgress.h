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
* This file contains the declaration of the functions which are related to the daily progress
* - displaying, editing, deleating of progress for specific date
* as well as the declarations and definitions of structures, needed for the organising of the information of users in files
*/

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
void deleteProgressForDate(std::vector<DailyProgress>& progressData, const std::string& date, const std::string& username);

void displayDailyProgress(const DailyProgress& progress, const User& user);
void editDailyProgress(DailyProgress& progress, const User& user);

void addMeal(const User& user, DailyProgress& progress);
void removeMeal(DailyProgress& progress, const User& user);
void addWorkout(DailyProgress& progress);
void removeWorkout(DailyProgress& progress);

#endif