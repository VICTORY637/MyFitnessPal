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
* This file contains the definition of the function which calculates the necessary daily intake of calories and macros

*
*/

#include "Calculations.h"
#include "User.h"
#include "Others.h"

#include <iostream>


void calculateCaloriesAndMacros(User& user) {
    double bmr = 0.0;
    if (user.gender == 'M') {
        bmr = 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
    }
    else if (user.gender == 'F') {
        bmr = 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
    }

    double activityMultiplier = 1.2;
    switch (user.activity) {
    case 1: activityMultiplier = 1.2; break;
    case 2: activityMultiplier = 1.375; break;
    case 3: activityMultiplier = 1.55; break;
    case 4: activityMultiplier = 1.725; break;
    case 5: activityMultiplier = 1.9; break;
    }

    const int dailyDeficit = 550;
    if (user.goal == 'L') {
        user.dailyCalories = round2(bmr * activityMultiplier - dailyDeficit);
    }
    else if (user.goal == 'G') {
        user.dailyCalories = round2(bmr * activityMultiplier + dailyDeficit);
    }
    else {
        user.dailyCalories = round2(bmr * activityMultiplier);
    }

    double proteinPercent = 0.25;
    double fatPercent = 0.30;
    double carbsPercent = 0.45;

    if (user.goal == 'L') {
        proteinPercent = 0.35;
        fatPercent = 0.30;
        carbsPercent = 0.35;
    }
    else if (user.goal == 'G') {
        proteinPercent = 0.40;
        fatPercent = 0.25;
        carbsPercent = 0.35;
    }

    user.protein = round2((user.dailyCalories * proteinPercent) / 4);
    user.fat = round2((user.dailyCalories * fatPercent) / 9);
    user.carbs = round2((user.dailyCalories * carbsPercent) / 4);
}

