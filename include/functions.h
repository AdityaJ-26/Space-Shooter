#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void intro();
int mainMenu();
void logic();
void update();
void game();
void quit();

//print
void display();

//input
void input();

//update
void moveObstacles();
void moveBullets();

//logic
void fire();
void spawnObstacles();
void playerCollisionCheck();
void bulletHitCheck();
void entityCheck();

#endif //FUNCTIONS_H