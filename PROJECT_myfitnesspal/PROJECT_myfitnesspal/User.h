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
    std::string goal = "";
};

extern std::vector<User> userDatabase;

void displayMainMenu();
void logIn();
void signIn();

#endif // USER_H
