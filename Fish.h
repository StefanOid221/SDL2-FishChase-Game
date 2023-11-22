#ifndef FISH_H
#define FISH_H

#include <SDL2/SDL.h>
#include "Constants.h"

struct Vector;

class Fish {
    public:
        //Fish constants
        static const int velocity = 4;
        float turnFactor;
        float centeringFactor = 0.0005;
        float avoidFactor = 0.05;
        float matchingFactor = 0.05;

        int PosX, PosY;

        Vector* vectorNew = nullptr;

        double angleRad;

        Fish();
        ~Fish();
        //Render
        void render();

        //Move
        void move();

        void initVel();

        void reflectAngle(bool horizontal);

        double distanceToFish(Fish& f);

        double distanceToPlayer(Vector v);

        void updateFlock(Fish (&fishes)[NUMBER_OF_FISHES], Vector playerPos);

    private:
        //Fish velocity
        float VelX, VelY;

        bool alive;
};
#endif