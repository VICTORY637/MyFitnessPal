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
* This file contains the declarations of the functions which operating wiyh files,
* keeping the user account information and the progress of the user for a specific date,
* as well as the declaration of global constant, which will be the name of the file with users
*/

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