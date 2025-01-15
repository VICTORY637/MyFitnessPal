#ifndef DAILY_PROGRESS_H
#define DAILY_PROGRESS_H

#include <string>
#include <vector>

struct DailyProgress {
    std::string date;                       
    std::vector<std::string> meals;        
    std::vector<std::string> workouts;      
    int waterCups = 0;                      
    int calorieBalance = 0;                 
};


void saveDailyProgress(const std::vector<DailyProgress>& progressData, const std::string& filename);
std::vector<DailyProgress> loadDailyProgress(const std::string& filename);
void displayDailyProgress(const DailyProgress& progress);
void editDailyProgress(DailyProgress& progress);

#endif // DAILY_PROGRESS_H
