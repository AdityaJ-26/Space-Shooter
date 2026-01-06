#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int BOUNDARY_LENGTH = 30;
constexpr int BOUNDARY_HEIGHT = 20;
constexpr int PLAYER_LIVES = 3;
constexpr int OBSTACLE_HEALTH = 20;
constexpr int O2P_HIT_DAMAGE = 50;
constexpr int B2O_HIT_DAMAGE = 20;
constexpr int MAX_OBSTACLES = 5;
constexpr int MAX_BULLETS = 10;

enum InputKeys {
    UP_KEY = 1,
    RIGHT_KEY = 2,
    DOWN_KEY = 3,
    LEFT_KEY = 4,
    IDLE = 0,
};

#endif //CONSTANTS_H