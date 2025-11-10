#include <iostream>
#include <windows.h>
#include <vector>   
#include "lib\class.h"
#include "lib\constants.h"
#include "lib\functions.h"


//############################################################
void logic() {
    spawnObstacles();
    fire();
    playerCollisionCheck();
    bulletHitCheck();
    entityCheck();
}


//############################################################
void update() {
    GameVariable::playerShip->move();
    moveObstacles();
    moveBullets();
}


//############################################################
//                       Main
//############################################################
int main() {

    intro();

    srand(time(0));
    while (!GameVariable::gameOver) {
        input();
        update();
        logic();
        if (GameVariable::gameOver) break;
        display();
        Sleep(100);
    }

    if (GameVariable::gameOver) {
        system("cls");
        std::cout << "||||||      ||      |||    |||  ||||||    ||||||  |||    |||  ||||||  ||||||" << std::endl;
        std::cout << "||         ||||     || |||| ||  ||        ||  ||   ||    ||   ||      ||  ||" << std::endl;
        std::cout << "||||||    ||  ||    ||  ||  ||  ||||||    ||  ||    ||  ||    ||||||  ||||||" << std::endl;
        std::cout << "||  ||   ||||||||   ||      ||  ||        ||  ||     ||||     ||      ||  ||" << std::endl;
        std::cout << "||||||  ||      ||  ||      ||  ||||||    ||||||      ||      ||||||  ||  ||" << std::endl;
    }
    return 0;
}

