#include <iostream>
#include <ctime>
#include "User.logging.h"
#include "FileManager.h"
#include "Menu2.h"
#include "DailyProgress.h"

int main() {
    loadUsersFromFile();

    displayMainMenu();

    /*if (currentUser) {
        std::vector<DailyProgress> progressData = loadDailyProgress("progress.txt");

        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);
        char dateBuffer[11];
        strftime(dateBuffer, 11, "%Y-%m-%d", &localTime);
        std::string todayDate(dateBuffer);

        DailyProgress currentProgress;
        currentProgress.date = todayDate;

        auto it = std::find_if(progressData.begin(), progressData.end(), [&](const DailyProgress& dp) {
            return dp.date == todayDate;
            });

        if (it != progressData.end()) {
            currentProgress = *it;
        }
        else {
            progressData.push_back(currentProgress);
        }

        displayMenu2(*currentUser, currentProgress);

        auto updateIt = std::find_if(progressData.begin(), progressData.end(), [&](const DailyProgress& dp) {
            return dp.date == currentProgress.date;
            });

        if (updateIt != progressData.end()) {
            *updateIt = currentProgress;
        }

        saveDailyProgress(progressData, "progress.txt");
    }
    else {
        std::cout << "No user logged in. Exiting program.\n";
    }

    saveUsersToFile();

    return 0;
}*/

    if (currentUser) {
        std::string filename = "progress_" + currentUser->username + ".txt";
        std::vector<DailyProgress> progressData = loadDailyProgress(filename);

        DailyProgress currentProgress;
        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);
        char dateBuffer[11];
        strftime(dateBuffer, 11, "%Y-%m-%d", &localTime);
        std::string todayDate(dateBuffer);


        auto it = std::find_if(progressData.begin(), progressData.end(), [&](const DailyProgress& dp) {
            return dp.date == todayDate;
            });

        if (it != progressData.end()) {
            currentProgress = *it;
        }
        else {
            currentProgress.date = todayDate;
            progressData.push_back(currentProgress);
        }

        displayMenu2(*currentUser, currentProgress);





        auto updateIt = std::find_if(progressData.begin(), progressData.end(), [&](const DailyProgress& dp) {
            return dp.date == currentProgress.date;
            });

        if (updateIt != progressData.end()) {
            *updateIt = currentProgress;
        }

        saveDailyProgress(progressData, filename);
    }
    else {
        std::cout << "No user logged in. Exiting program.\n";
    }

    saveUsersToFile();
}
