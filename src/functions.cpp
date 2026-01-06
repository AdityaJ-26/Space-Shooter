#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include "..\include\functions.h"
#include "..\include\constants.h"
#include "..\include\class.h"
#include "..\include\menus.h"


void intro() {
    std::cout << "||||||  ||||||  ||||||  ||||||  ||||||    ||||||  ||  ||  ||||||  ||||||  ||||||  |||||  |||||" << std::endl;
    std::cout << "||      ||  ||  ||  ||  ||      ||        ||      ||  ||  ||  ||  ||  ||    ||    ||     ||  ||" << std::endl;
    std::cout << "||||||  ||||||  ||||||  ||      ||||||    ||||||  ||||||  ||  ||  ||  ||    ||    |||||  |||||" << std::endl;
    std::cout << "    ||  ||      ||  ||  ||      ||            ||  ||  ||  ||  ||  ||  ||    ||    ||     || ||" << std::endl;
    std::cout << "||||||  ||      ||  ||  ||||||  ||||||    ||||||  ||  ||  ||||||  ||||||    ||    |||||  ||  ||" << std::endl;
    std::cout << "                                                                                           v2.0" << std::endl;
    std::cout << "Press Enter to Continue...";
    getchar();
    return;
}

int mainMenu() {
    int opt;
    MainMenu *menu = new MainMenu();
    while (true) {
        system("cls");
        menu->printMenu();
        opt = menu->opt();
        menu->input();
        Sleep(200);
        if (menu->optSelected()) {
            break;
        }
    }
    return opt;
}

void logic() {
    spawnObstacles();
    fire();
    playerCollisionCheck();
    bulletHitCheck();
    entityCheck();
}

void update() {
    GameVariable::playerShip->move();
    moveObstacles();
    moveBullets();
}

void game() {
    while (!GameVariable::gameOver) {
        input();
        update();
        logic();
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
}

void quit() {
    std::cout << std::endl << "Press Enter to Exit...";
    getchar();
    exit(0);
}

//############################################################
//                      Input
//############################################################
void input() {
    if (GetAsyncKeyState(0x57)) {
        GameVariable::playerShip->setKey(UP_KEY);
    }
    else if (GetAsyncKeyState(0x41)) {
        GameVariable::playerShip->setKey(LEFT_KEY);
    }
    else if (GetAsyncKeyState(0x53)) {
        GameVariable::playerShip->setKey(DOWN_KEY);
    }
    else if (GetAsyncKeyState(0x44)) {
        GameVariable::playerShip->setKey(RIGHT_KEY);
    }
    else if (GetAsyncKeyState(0x20)) {
        GameVariable::playerShip->setFireKey(1);
    }
}


//############################################################
//                     Print
//############################################################
void display() {
    system("cls");
    for (int y=0; y<=BOUNDARY_HEIGHT; y++) {
        for (int x=0; x<=BOUNDARY_LENGTH; x++) {
            if (GameVariable::playerShip->matchCoordinates(x, y)) {
                GameVariable::playerShip->print();
                continue;
            }
            bool printed = false;
            for (const auto& obstacle : GameVariable::obstacleList) {
                if (obstacle->matchCoordinates(x, y)) {
                    obstacle->print();
                    printed = true;
                    break;
                }
            }
            if (printed) continue;
            for (const auto& bullet : GameVariable::bulletList)  {
                if (bullet->matchCoordinates(x, y)) {
                    bullet->print();
                    printed = true;
                    break;
                }
            }
            if (printed) continue;
            if (x == BOUNDARY_LENGTH || x == 0 || y == BOUNDARY_HEIGHT || y == 0) {
                std::cout << "#";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "SCORE - " << GameVariable::playerShip->getScore() << std::endl;
    std::cout << "LIVES - ";
    for (int i{ 0 }; i < GameVariable::playerShip->livesCount(); i++)
        std::cout << "*";

}


//############################################################
//                     Update
//############################################################
void moveObstacles() {
    for (auto obstacle : GameVariable::obstacleList) {
        obstacle->move();
    }
}
void spawnObstacles() {
    auto& obstacle = GameVariable::obstacleList;
    if (obstacle.size() >= MAX_OBSTACLES) return;
    obstacle.push_back(new Obstacle());
}
void fire() {
    auto& ship = GameVariable::playerShip;
    if (ship->checkFireKey() && GameVariable::bulletList.size() < MAX_BULLETS) {
        int x = ship->getX(), y = ship->getY();
        GameVariable::bulletList.push_back(new Bullet(x, y-1));
        ship->setFireKey(0);
    }
}
void moveBullets() {
    for (auto& bullet : GameVariable::bulletList) {
        bullet->move();
    }
}


//############################################################
//                     Logic
//############################################################
void playerCollisionCheck() {
    auto& obstacles = GameVariable::obstacleList;
    for (int i=0; i<obstacles.size();) {
        int x = obstacles[i]->getX(), y = obstacles[i]->getY();
        if (GameVariable::playerShip->matchCoordinates(x, y)) {
            GameVariable::playerShip->livesUpdate();
            delete obstacles[i];
            obstacles.erase(obstacles.begin()+i);
        }
        else i++;
    }
}  
void bulletHitCheck() {
    auto& bullets = GameVariable::bulletList;
    for (int i=0; i<bullets.size();) {
        bool hit = false;
        for (auto& obstacle : GameVariable::obstacleList) {
            int x = obstacle->getX(), y = obstacle->getY();
            if (bullets[i]->matchCoordinates(x, y) || bullets[i]->matchCoordinates(x, y-1)) {
                obstacle->healthUpdate(B2O_HIT_DAMAGE);
                delete bullets[i];
                bullets.erase(bullets.begin()+i);
                hit = true;
                GameVariable::playerShip->hit();
                break;
            }
        }
        if (!hit) i++;
    }
}
void entityCheck() {
    //health check
    if (GameVariable::playerShip->livesCount() == 0) {
        delete(GameVariable::playerShip);
        GameVariable::gameOver = true;
    }
    auto& bullets = GameVariable::bulletList;
    for (int i=0; i<bullets.size();) {
        if (bullets[i]->outOfBound()) {
            delete bullets[i];
            bullets.erase(bullets.begin()+i);
        }
        else i++;
    }
    auto& obstacles = GameVariable::obstacleList;
    for (int i=0; i<obstacles.size();) {
        if (obstacles[i]->noHealth() || obstacles[i]->outOfBound()) {
            delete obstacles[i];
            obstacles.erase(obstacles.begin()+i);
        }
        else i++;
    }
}

