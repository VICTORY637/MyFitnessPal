#ifndef OTHERS_H
#define OTHRS_H

#include <string>

char toUpper(char& letter);
int inputIntValidatedData(const std::string& prompt, int min, int max);
double inputDoubleValidatedData(const std::string& prompt, double min, double max);
char inputCharValidatedData(const std::string& prompt, const char* validChars, int validCharCount);
std::string getCurrentDate();

#endif