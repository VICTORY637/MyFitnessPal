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

#ifndef OTHERS_H
#define OTHRS_H

#include <string>

char toUpper(char& letter);
int inputIntValidatedData(const std::string& prompt, int min, int max);
double inputDoubleValidatedData(const std::string& prompt, double min, double max);
char inputCharValidatedData(const std::string& prompt, const char* validChars, int validCharCount);
std::string getCurrentDate();

#endif