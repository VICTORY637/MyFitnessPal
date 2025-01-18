#include "Others.h"

#include <iostream>
#include <string>
#include <ctime>



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
        std::cout << "Invalid input. Please enter a value between " << min << " and " << max << ".\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

double inputDoubleValidatedData(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (value >= min && value <= max) {
            return value;
        }

        std::cout << "Invalid input. Please enter a value between " << min << " and " << max << ".\n";
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
            std::cout << validChars[i] << (i < validCharCount - 1 ? ", " : ".\n");
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}


std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm now; 
    localtime_s(&now, &t);
    return std::to_string(1900 + now.tm_year) + "-" +
        (now.tm_mon < 9 ? "0" : "") + std::to_string(1 + now.tm_mon) + "-" +
        (now.tm_mday < 10 ? "0" : "") + std::to_string(now.tm_mday);
}
