#include "Menu.h"
#include "User.h"
#include "DailyProgress.h"
#include "FileManager.h"
#include "Calculations.h"
#include "Others.h"

#include <iostream>
#include <vector>

int main() {
    // Load existing users from file
    loadUsersFromFile();

    // Display the main menu
    displayMainMenu();

    if (currentUser) {
        // Load or initialize daily progress for the current user
        std::string currentDate = getCurrentDate();
        DailyProgress currentProgress;
        std::vector<DailyProgress> userProgress = loadDailyProgress(currentUser->username);

        // Check if there's progress for today
        bool progressFound = false;
        for (auto& progress : userProgress) {
            if (progress.date == currentDate) {
                currentProgress = progress;
                progressFound = true;
                break;
            }
        }

        if (!progressFound) {
            // Initialize new progress for the day
            currentProgress.date = currentDate;
        }

        // Show the user's menu2
        displayMenu2(*currentUser, currentProgress);

        // Save the updated progress to file
        if (progressFound) {
            for (auto& progress : userProgress) {
                if (progress.date == currentDate) {
                    progress = currentProgress;
                    break;
                }
            }
        }
        else {
            userProgress.push_back(currentProgress);
        }

        saveDailyProgress(userProgress, currentUser->username);

        // Reset user pointer to allow re-login or exit
        currentUser = nullptr;
    }

    // Save users to file before exiting
    saveUsersToFile();

    return 0;
}
