#include <iostream>
#include <windows.h>
#include <vector>   
#include <iomanip>
#include "include\class.h"
#include "include\constants.h"
#include "include\functions.h"
#include "include\menus.h"

int main() {

    intro();

    int opt{ 0 };
    while (true) {

        opt = mainMenu();

        if (opt == 1) {
            std::string name = gameMenu();
            GameVariable::playerShip->setName(name);
            game();
            std::cout << "NAME" << std::setw(24) << "SCORE" << std::endl;
            std::cout << name << std::setw(22) << GameVariable::playerShip->getScore() << std::endl;
            std::cout << std::endl << "Press Enter to Retur to Main Menu";
            getchar();
        }

        if (opt == 2) {
            quit();
        }
    }

    srand(time(0));
    return 0;
}

