#ifndef DAILY_PROGRESS_H
#define DAILY_PROGRESS_H

#include <string>
#include <vector>
#include "User.logging.h"

struct DailyProgress {
    std::string date;
    double calorieBalance = 0.0;
    double proteinIntake = 0.0;
    double fatIntake = 0.0;
    double carbsIntake = 0.0;
    int waterCups = 0;
    std::vector<std::string> meals;
    std::vector<std::string> workouts;
};

void saveDailyProgress(const std::vector<DailyProgress>& progressData, const std::string& filename);
std::vector<DailyProgress> loadDailyProgress(const std::string& filename);

std::vector<DailyProgress> loadDailyProgress(const std::string& filename);
void displayDailyProgress(const DailyProgress& progress, const User& user);
void editDailyProgress(DailyProgress& progress, const User& user);
#endif // DAILY_PROGRESS_H
