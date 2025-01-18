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
* This file contains the definitions of the functions which will be the MENUS
* (a description of the menu structure can be found in the file "Structure.plan.txt"
*/

#ifndef MENU_H
#define MENU_H

#include "User.h"
#include "DailyProgress.h"

void displayMainMenu();
void displayMenu2(User& user, DailyProgress& currentProgress);
void displayHistoryMenu(User& user);

#endif