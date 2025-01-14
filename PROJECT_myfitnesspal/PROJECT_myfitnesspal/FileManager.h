#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

extern const std::string userDatabaseFile;

void saveUsersToFile();
void loadUsersFromFile();

#endif // FILE_MANAGER_H
