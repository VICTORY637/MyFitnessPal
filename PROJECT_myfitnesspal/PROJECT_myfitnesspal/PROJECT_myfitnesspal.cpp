#include <iostream>
#include "User.logging.h"
#include "FileManager.h"

int main() {
    loadUsersFromFile();
    displayMainMenu();
    saveUsersToFile();
    return 0;
}

