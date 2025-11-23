#include <iostream>
#include "..\lib\class.h"

//############################################################
//                     Coordinate
//############################################################
Coordinate::Coordinate(int x, int y) {
    this->xCoordinate = x % BOUNDARY_LENGTH;
    this->yCoordinate = y % BOUNDARY_HEIGHT;
}

//############################################################
//                     SpaceShip
//############################################################
SpaceShip::SpaceShip(int x, int y) {
    this->xCoordinate = x % BOUNDARY_LENGTH;
    this->yCoordinate = y % BOUNDARY_HEIGHT;
    this->key = IDLE;
}
void SpaceShip::setKey(InputKeys key) {
    this->key = key;
} 
void SpaceShip::setFireKey(bool x) {
    this->fireTrigger = x;
}
bool SpaceShip::checkFireKey() {
    return this->fireTrigger;
}
void SpaceShip::move() {
    switch(this->key) {
        case MOVE_UP:
            if (this->yCoordinate < 1) break;
            this->yCoordinate--;
            break;
        case MOVE_LEFT:
            if (this->xCoordinate < 1) break;
            this->xCoordinate--;
            break;
        case MOVE_DOWN:
            if (this->yCoordinate > BOUNDARY_HEIGHT-1) break;
            this->yCoordinate++;
            break;
        case MOVE_RIGHT:
            if (this->xCoordinate > BOUNDARY_LENGTH-1) break;
            this->xCoordinate++;
            break;
        default:
            break;
    }
    this->key = IDLE;
}
void SpaceShip::print() {
    std::cout << "^";

}
bool SpaceShip::matchCoordinates(int x, int y) {
    return (this->xCoordinate == x && this->yCoordinate == y);
}
int SpaceShip::getX() {
    return this->xCoordinate;
}
int SpaceShip::getY() {
    return this->yCoordinate;
}
void SpaceShip::healthUpdate(int damage) {
    this->health -= damage;
}
bool SpaceShip::noHealth() {
    return (this->health <= 0);
}

//############################################################
//                     Obstacles
//############################################################
void Obstacle::move() {
    this->yCoordinate++;
}
void Obstacle::print() {
    std::cout << char(254);
}
bool Obstacle::matchCoordinates(int x, int y) {
    return (this->xCoordinate == x && this->yCoordinate == y);
}
bool Obstacle::outOfBound() {
    return (this->yCoordinate > BOUNDARY_HEIGHT-1);
}
int Obstacle::getX() {
    return this->xCoordinate;
}
int Obstacle::getY() {
    return this->yCoordinate;
}
void Obstacle::healthUpdate(int damage) {
    this->health -= damage;
}
bool Obstacle::noHealth() {
    return (this->health <= 0);
}

//############################################################
//                     Game Variables
//############################################################
SpaceShip* GameVariable::playerShip = new SpaceShip(BOUNDARY_LENGTH/2, BOUNDARY_HEIGHT-2);
bool GameVariable::gameOver = false;
std::vector<Obstacle*> GameVariable::obstacleList;
std::vector<Bullet*> GameVariable::bulletList;


//############################################################
//                        Bullets
//############################################################
Bullet::Bullet(int x, int y) : Coordinate(x, y) {}
bool Bullet::matchCoordinates(int x, int y) {
    return (this->xCoordinate == x && this->yCoordinate == y);
}
bool Bullet::outOfBound() {
    return (this->yCoordinate < 1);
}
void Bullet::print() {
    std::cout << "*";
}
void Bullet::move() {
    this->yCoordinate--;
}