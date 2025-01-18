#ifndef USER_H
#define USER_H

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

//global objects that can be defined and used in .cpp files without definition
extern User* currentUser;//pointer to the struct of data of the current user 
extern std::vector<User> userDatabase; //vector with elements of type User (array of struct)


void logIn();
void displayMotivationalQuote();
void signIn();
void editUserInformation(User& user);
void editPhisicalCharacteristics(User& user);
void printUserInformation(const User& user);

#endif