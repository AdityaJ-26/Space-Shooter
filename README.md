# **Space Shooter (v1.1)** 
A retro game created in C++.
> It is my first complete running project, open to suggestions, feedback is appreciated!
## **Features**
- CLI Based Game
- Basic 2D plane movement
- Obstacles (shooting and dodging)
- Collision mechanism (basic)
## **Gameplay**
- WSAD keys for movement of player(ship) 
- Spacebar for firing projectiles
- Dodge random falling obstacles
## **Project Structure**
  -Space-Shooter\
    |- [main.cpp](/main.cpp)   (main() file)\
    |- [src](/src)       (source files)\
    |- [lib](/lib)       (header files)\
## **Compiling**
Don't have a CMake or any auto build files\
Use command below in terminal inside main directory to manually compile code\
```
g++ main.cpp src\functions.cpp src\class.cpp -o game.exe
```
Run the game.exe file and play
## **Future Improvements**
- [X] Input buffer handling
- [ ] Sounds, textures & other assets
- [ ] Tick
- [ ] Game Menu
- [ ] Score System
