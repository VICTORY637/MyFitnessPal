#ifndef USER_H
#define USER_H

#include <string>
#include <vector>


struct User {
    std::string username = "";
    std::string password = "";
    int age = 0;
    char gender = 'U'; // U = Undefined
    double height = 0.0;
    double weight = 0.0;
    int activity = 0;
    char goal = 'L';
    char accountType = 'S'; // Default value
    double dailyCalories = 0.0;
    double protein = 0.0;
    double fat = 0.0;
    double carbs = 0.0;
};

extern std::vector<User> userDatabase;

void displayMainMenu();
void logIn();
void displayMotivationalQuote();
void signIn();

#endif // USER_H
