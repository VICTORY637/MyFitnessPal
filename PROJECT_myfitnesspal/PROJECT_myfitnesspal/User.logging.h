#ifndef USER_LOGGING_H
#define USER_LOGGING_H

#include <string>
#include <vector>

struct User {
    std::string username = "";
    std::string password = "";
    int age = 0;
    char gender = 'U';
    double height = 0.0;
    double weight = 0.0;
    int activity = 0;
    char goal = 'L';
    char accountType = 'S';
    double dailyCalories = 0.0;
    double protein = 0.0;
    double fat = 0.0;
    double carbs = 0.0;
};

extern User* currentUser;
extern std::vector<User> userDatabase;

void displayMainMenu();
void logIn();
void signIn();
void displayMotivationalQuote();

#endif // USER_LOGGING_H