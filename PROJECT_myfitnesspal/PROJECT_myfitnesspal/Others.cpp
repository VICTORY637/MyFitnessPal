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
* This file contains the declarations of other useful functions which are not specifical for that project
*/

#include "Others.h"

#include <iostream>
#include <string>
#include <ctime>




bool isValidFileName(const std::string& username) {
    for (char c : username) {
        if (!((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            (c == '.') || (c == '_')))
        {
            return false;
        }
    }
    return true;
}



double bigger(double a, double b) {
    return (a > b) ? a : b;
}



char toUpper(char& letter) {
    if (letter >= 'a' && letter <= 'z') letter = letter - ('a' - 'A');
    return letter;
}


int inputIntValidatedData(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (value >= min && value <= max) {
            return value;
        }
        std::cout << "Invalid input. Please enter a value between " << min << " and " << max << ".\n\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}


double inputDoubleValidatedData(const std::string& prompt, double min, double max) {
    const double EPSILON = 0.000000001;
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if ((value > min - EPSILON) && (value < max + EPSILON)) {
            return value;
        }
        std::cout << "Invalid input. Please enter a value between " << min << " and " << max << ".\n\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}



char inputCharValidatedData(const std::string& prompt, const char* validChars, int validCharCount) {
    char value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        value = toUpper(value);

        for (int i = 0; i < validCharCount; ++i) {
            if (value == validChars[i]) {
                return value;
            }
        }

        std::cout << "Invalid input. Please enter one of the following: ";
        for (int i = 0; i < validCharCount; ++i) {
            std::cout << validChars[i] << (i < validCharCount - 1 ? ", " : ".\n\n");
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}



std::string getCurrentDate() {
    std::time_t t = std::time(nullptr); // returns the current time in seconds since January 1, 1970. (Epoch time)
    std::tm now; //structure that contains the time information separated (year, month, day, etc.)
    localtime_s(&now, &t); // fills now with the local time

    /* After executing localtime_s(), the now structure will contain:
        now.tm_year =        Year - 1900                              -> 125 (if year is 2025)
        now.tm_mon =         Month (0 = January, 11 = December)       -> 5 (for June)
        now.tm_mday =        Day of the month (1 - 31)                -> 1 for january         */

    return std::to_string(1900 + now.tm_year) + "-" + // std::to_string() is a function from std::string that converts numbers to a string (std::string)
        (now.tm_mon < 9 ? "0" : "") + std::to_string(1 + now.tm_mon) + "-" +
        (now.tm_mday < 10 ? "0" : "") + std::to_string(now.tm_mday);
}



double round2(double value) {
    value = (value * 100.0 + 0.5);
    int temp = static_cast<int>(value);
    return temp / 100.0;
}