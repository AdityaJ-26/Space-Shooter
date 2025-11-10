#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BOUNDARY_LENGTH 30
#define BOUNDARY_HEIGHT 20
#define PLAYER_HEALTH 100
#define OBSTACLE_HEALTH 20
#define O2P_HIT_DAMAGE 50
#define B2O_HIT_DAMAGE 20
#define MAX_OBSTACLES 5
#define MAX_BULLETS 10

enum InputKeys {
    MOVE_UP = 1,
    MOVE_RIGHT = 2,
    MOVE_DOWN = 3,
    MOVE_LEFT = 4,
    IDLE = 0, 
};

#endif //CONSTANTS_H

/*
tick system
playerShip new model
*/