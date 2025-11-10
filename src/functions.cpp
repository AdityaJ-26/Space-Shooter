#include <iostream>
#include <conio.h>
#include <vector>
#include "..\lib\functions.h"
#include "..\lib\constants.h"
#include "..\lib\class.h"


void intro() {
    std::cout << "||||||  ||||||  ||||||  ||||||  ||||||    ||||||  ||  ||  ||||||  ||||||  ||||||  |||||  |||||" << std::endl;
    std::cout << "||      ||  ||  ||  ||  ||      ||        ||      ||  ||  ||  ||  ||  ||    ||    ||     ||  ||" << std::endl;
    std::cout << "||||||  ||||||  ||||||  ||      ||||||    ||||||  ||||||  ||  ||  ||  ||    ||    |||||  |||||" << std::endl;
    std::cout << "    ||  ||      ||  ||  ||      ||            ||  ||  ||  ||  ||  ||  ||    ||    ||     || ||" << std::endl;
    std::cout << "||||||  ||      ||  ||  ||||||  ||||||    ||||||  ||  ||  ||||||  ||||||    ||    |||||  ||  ||" << std::endl;
    std::cout << "                                                                                           v1.0" << std::endl;
    std::cout << "Press Enter to Continue...";
    getchar();
    return;
}

//############################################################
//                      Input
//############################################################
void input() {
    if (_kbhit()) {
        switch( tolower(getch()) ) {
            case 'w':
                GameVariable::playerShip->setKey(MOVE_UP);
                break;
            case 'a':
                GameVariable::playerShip->setKey(MOVE_LEFT);
                break;
            case 's':
                GameVariable::playerShip->setKey(MOVE_DOWN);
                break;
            case 'd':
                GameVariable::playerShip->setKey(MOVE_RIGHT);
                break;
            case ' ':
                GameVariable::playerShip->setFireKey(true);
                break;
            default:
                break;
        }
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
            GameVariable::playerShip->healthUpdate(O2P_HIT_DAMAGE);
            delete obstacles[i];
            obstacles.erase(obstacles.begin()+i);
        }
        else i++;
    }
}  
void bulletHitCheck() {
    auto& bullets = GameVariable::bulletList;
    for (int i=0; i<bullets.size(); i++) {
        for (auto& obstacle : GameVariable::obstacleList) {
            int x = obstacle->getX(), y = obstacle->getY();
            if (bullets[i]->matchCoordinates(x, y)) {
                obstacle->healthUpdate(B2O_HIT_DAMAGE);
                delete bullets[i];
                bullets.erase(bullets.begin()+i);
                i--;
                break;
            }
        }
    }
}
void entityCheck() {
    //health check
    if (GameVariable::playerShip->noHealth()) {
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

