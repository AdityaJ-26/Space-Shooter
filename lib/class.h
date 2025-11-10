#ifndef CLASS_H
#define CLASS_H

#include <vector>
#include "constants.h"

//############################################################
class Coordinate {
    public:
        int xCoordinate {1}, yCoordinate{1};
        Coordinate() = default;
        Coordinate(int, int);
};


//############################################################
class Obstacle : private Coordinate {
    private:
        int health{OBSTACLE_HEALTH};
        // int radius{1};
    public:
        Obstacle() : Coordinate(rand()%BOUNDARY_LENGTH, 1) {};
        void move();
        void print();
        bool outOfBound();
        int getX();
        int getY();
        bool matchCoordinates(int, int);
        void healthUpdate(int);
        bool noHealth();
};


//############################################################
class Bullet : private Coordinate {
    private:
        const int damage{B2O_HIT_DAMAGE};
    public:
        Bullet(int, int);
        bool matchCoordinates(int, int);
        bool outOfBound();
        void print();
        void move();
};


//############################################################
class SpaceShip : private Coordinate {
    private:
        int health{PLAYER_HEALTH};
        InputKeys key;
        bool fireTrigger{0};
        const int width{2};
    public:
        SpaceShip(int, int);
        void setKey(InputKeys);
        void setFireKey(bool);
        bool checkFireKey();
        void move();
        void print();
        int getX();
        int getY();
        bool matchCoordinates(int, int);
        void healthUpdate(int damage);
        bool noHealth();
};


//############################################################
class GameVariable {
    public:
        static SpaceShip *playerShip;
        static std::vector<Obstacle *> obstacleList;
        static std::vector<Bullet *> bulletList;
        static bool gameOver;
};

#endif //CLASS_H