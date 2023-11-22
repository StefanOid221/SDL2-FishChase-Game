#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Constants.h"

struct Vector;

class Player  {

    public:

        //Player constants
        static const int velocity = 8;
        static const int PLAYER_WIDTH = 33;
        static const int PLAYER_HEIGTH = 86;

        Vector* vectorNew = nullptr;

        double angleRad;

        //Initializer
        Player();

        ~Player();
        // void move();

        //Events
        void handleEvent( SDL_Event* e );

        //Render
        void render();

        //Move
        void move();

        Vector getPosition() const;

        float getVelX();
        float getVelY();

    private:
        //Position
        int PosX, PosY;

        //Velocity
        float VelX, VelY;

        bool buttonPressed;

        
};

#endif