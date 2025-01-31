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
* This file contains the declaration of the functions which are related to the logging in,
* signing in and editing the personal information of the users
* as well as the declaration and definition of structure, needed for the organising of the
* information of users in file
* as well as the declarations of two global constants
* as well as the declaration of the generationg a random quote function
*/

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

extern User* currentUser;//pointer to the struct of data of the current user 
extern std::vector<User> userDatabase; //vector with elements of type User


void logIn();
void displayMotivationalQuote();
void signIn();
void editUserInformation(User& user);
void editPhisicalCharacteristics(User& user);
void printUserInformation(const User& user);
std::string getValidUsername(const std::vector<User>& userDatabase);

#endif