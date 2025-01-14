#include "Calculations.h"
#include <iostream>

void calculateCaloriesAndMacros(User& user) {
    // BMR formula
    double bmr = 0.0;
    if (user.gender == 'M') {
        bmr = 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
    }
    else if (user.gender == 'F') {
        bmr = 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
    }

    // Activity multiplier
    double activityMultiplier = 1.2;
    switch (user.activity) {
    case 1: activityMultiplier = 1.2; break;
    case 2: activityMultiplier = 1.375; break;
    case 3: activityMultiplier = 1.55; break;
    case 4: activityMultiplier = 1.725; break;
    case 5: activityMultiplier = 1.9; break;
    }

    // Calculate daily calories (TDEE)
    const int dailyDeficit = 550; //for changing the weight with 0.5 kg per week
    if (user.goal == 'L') { // Lose weight
        user.dailyCalories = bmr * activityMultiplier - dailyDeficit;
    }
    else if (user.goal == 'G') { // Gain
        user.dailyCalories = bmr * activityMultiplier + dailyDeficit;
    }
    else user.dailyCalories = bmr * activityMultiplier; //Maintain

    // Calculate macros for Premium accounts

    double proteinPercent = 0.25; // Default for maintenance
    double fatPercent = 0.30;
    double carbsPercent = 0.45;

    if (user.goal == 'L') { // Lose weight
        proteinPercent = 0.35;
        fatPercent = 0.30;
        carbsPercent = 0.35;
    }
    else if (user.goal == 'G') { // Gain muscle
        proteinPercent = 0.40;
        fatPercent = 0.25;
        carbsPercent = 0.35;
    }

    user.protein = (user.dailyCalories * proteinPercent) / 4; // Protein: 4 kcal/g
    user.fat = (user.dailyCalories * fatPercent) / 9;         // Fat: 9 kcal/g
    user.carbs = (user.dailyCalories * carbsPercent) / 4;     // Carbs: 4 kcal/g
    
}
