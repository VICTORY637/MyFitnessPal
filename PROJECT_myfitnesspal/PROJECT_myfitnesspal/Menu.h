#ifndef MENU_H
#define MENU_H

#include "User.h"
#include "DailyProgress.h"

void displayMainMenu();
void displayMenu2(User& user, DailyProgress& currentProgress);
void displayHistoryMenu(User& user);

#endif