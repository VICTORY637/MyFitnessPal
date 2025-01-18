#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "DailyProgress.h"

#include <string>
#include <vector>

extern const std::string userDatabaseFile;

void saveUsersToFile();
void loadUsersFromFile();
void saveDailyProgress(const std::vector<DailyProgress>& progressData, const std::string& username);
std::vector<DailyProgress> loadDailyProgress(const std::string& username);

#endif