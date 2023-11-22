#ifndef UTIL_H
#define UTIL_H

#include "Constants.h"
#include "Player.h" 
#include "Fish.h" 

struct Vector {
    int x, y;
};
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

bool checkCollision(int x1, int y1, int x2, int y2);

void spawnFishes(const Player& player, Fish (&fishes)[NUMBER_OF_FISHES]);



#endif