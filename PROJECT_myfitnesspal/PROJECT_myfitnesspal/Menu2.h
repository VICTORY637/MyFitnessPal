#ifndef MENU2_H
#define MENU2_H

#include "User.logging.h"
#include "DailyProgress.h"


void displayMenu2(User& user, DailyProgress& currentProgress);

void displayDailyProgress(const DailyProgress& progress, const User& user);
void printUserInformation(const User& user);
void editUserInformation(User& user);
void editPhisicalCharacteristics(User& user);

#endif // MENU2_H
