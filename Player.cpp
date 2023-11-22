#include "Player.h"
#include "Globals.h"
#include "Util.h"
#include "Constants.h"
#include <cmath>
#include <iostream>

Player::Player() {
    PosX = SCREEN_WIDTH/2;
    PosY = SCREEN_HEIGHT/2;

    VelX = 0;
    VelY = 0;

    buttonPressed = false;
    angleRad = 0;

    if (!vectorNew){
        vectorNew = new Vector {PosX, PosY};
    }

   

}

Player:: ~Player() {
        if (vectorNew){
            delete vectorNew;
        }
    };

// void Player:: move(){

// }

void Player::handleEvent(SDL_Event* e) {

    if( e->type == SDL_MOUSEMOTION)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        vectorNew->x = x;
        vectorNew->y = y;
    }
    if (e->type == SDL_MOUSEBUTTONDOWN){
        buttonPressed = true;
    }
    if (e->type == SDL_MOUSEBUTTONUP){
        buttonPressed = false;
    }
}

void Player:: render() {

    double angle = angleRad  * 180 / M_PI;
    angle += 90;

    gPlayerTexture.render(PosX, PosY, nullptr, angle);
}

void Player::move()
{
    double deltaX = vectorNew->x - PosX;
    double deltaY = vectorNew->y - PosY;
    angleRad = atan2(deltaY, deltaX); // Convert to radians
    if(buttonPressed){
        VelX = velocity * cos(angleRad);
        VelY = velocity * sin(angleRad);
    }
    else {
        if (VelX <= 0.001 && VelY <= 0.001){
            VelX = 0;
            VelY = 0;
        }
        else{
            VelX -= VelX/2;
            VelY -= VelY/2;
        }
    }
    PosX += VelX;

    //If the dot went too far to the left or right
    if( ( PosX  < 0 ) || ( PosX + PLAYER_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        PosX -= VelX;
    }

    //Move the dot up or down
    PosY += VelY;

    //If the dot went too far up or down
    if( ( PosY < 0 ) || ( PosY + PLAYER_HEIGTH > SCREEN_HEIGHT ) )
    {
        PosY -= VelY;
    }
    
}
Vector Player::getPosition() const{

    return Vector{PosX, PosY};
    
}

float Player::getVelX() {
    return VelX;
}
float Player::getVelY() {
    return VelY;
}