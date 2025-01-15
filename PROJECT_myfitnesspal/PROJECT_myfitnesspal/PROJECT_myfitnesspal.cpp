#include <iostream>
#include "User.logging.h"
#include "FileManager.h"
#include "Menu2.h"
#include "DailyProgress.h"

int main() {
    
    loadUsersFromFile();

    
    std::vector<DailyProgress> progressData = loadDailyProgress("progress.txt");

   
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char dateBuffer[11];
    strftime(dateBuffer, 11, "%Y-%m-%d", localTime);
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

    displayMainMenu();

   
    User currentUser = {/*???????? ?? ??????? ??????????*/ };

    
    displayMenu2(currentUser, currentProgress);

    ?
    auto updateIt = std::find_if(progressData.begin(), progressData.end(), [&](const DailyProgress& dp) {
        return dp.date == currentProgress.date;
        });

    if (updateIt != progressData.end()) {
        *updateIt = currentProgress;
    }

    saveUsersToFile();
    saveDailyProgress(progressData, "progress.txt");

    return 0;
}
