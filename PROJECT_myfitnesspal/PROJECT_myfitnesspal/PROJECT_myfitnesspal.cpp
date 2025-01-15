#include <iostream>
#include "User.logging.h"
#include "FileManager.h"
#include "Menu2.h"

int main() {
    loadUsersFromFile();
    displayMainMenu();
    saveUsersToFile();
    return 0;
}

