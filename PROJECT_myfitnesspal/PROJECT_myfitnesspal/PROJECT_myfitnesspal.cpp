#include <iostream>
#include "User.h"
#include "FileManager.h"

int main() {
    loadUsersFromFile();
    displayMainMenu();
    saveUsersToFile();
    return 0;
}

