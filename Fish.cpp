#include "Fish.h"
#include "Globals.h"
#include "Constants.h"
#include "Util.h"
#include <cmath>
#include <iostream>

Fish::Fish(){
    PosX = 0;
    PosY = 0;
    alive = true;

    VelX = 0;
    VelY = 0;
    vectorNew = nullptr;
    angleRad = 0;
    turnFactor = 0.5;
    if (!vectorNew){
        vectorNew = new Vector {PosX, PosY};
    }

   
}
Fish:: ~Fish() {
        if (vectorNew){
            delete vectorNew;
        }
    };

void Fish:: render() {

    if (alive)
    {
    double angle = angleRad  * 180 / M_PI;
    angle += 180;

    gFishTexture.render(PosX, PosY, nullptr, angle);
    }
}

double Fish:: distanceToFish(Fish& f2){
    return sqrt(pow(PosX - f2.PosX, 2) + pow(PosY - f2.PosY, 2));
}

double Fish:: distanceToPlayer(Vector v){
    return sqrt(pow(PosX - v.x, 2) + pow(PosY - v.y, 2));
}

void Fish:: initVel() {
    double deltaX = vectorNew->x - PosX;
    double deltaY = vectorNew->y - PosY;
    angleRad = atan2(deltaY, deltaX); // Convert to radians
    VelX = velocity * cos(angleRad);
    VelY = velocity * sin(angleRad);
}

void Fish::reflectAngle(bool horizontal) {
    if (horizontal) {
        // Reflect the angle along the X-axis
        angleRad = M_PI - angleRad; // Reverse the direction along X-axis
    }

    else {
        // Reflect the angle along the Y-axis
        angleRad = -angleRad; // Reverse the direction along Y-axis
    }

    // Recalculate VelX and VelY based on the updated angle
    VelX = velocity * cos(angleRad);
    VelY = velocity * sin(angleRad);
    
}


void Fish::move()
{
    if( ( PosX  < 0 ))
    {
        VelX = VelX + turnFactor;
        
    }
    if (PosX + FISH_WIDTH > SCREEN_WIDTH){
        VelX = VelX - turnFactor;
    }
    if(PosY < 0 )
    {
        VelY = VelY + turnFactor;
    } 
    if (PosY + FISH_HEIGTH > SCREEN_HEIGHT){
        VelY = VelY - turnFactor;
    }
     PosX += VelX;
     PosY += VelY;
}

bool operator != (const Fish& f1, const Fish& f2) {
    return !(f1.PosX == f2.PosX && f1.PosY == f2.PosY);
}

void Fish:: updateFlock(Fish (&fishes)[NUMBER_OF_FISHES], Vector playerPos){

    float avVelX = 0;
    float avVelY = 0;
    int avPosX = 0;
    int avPosY = 0;
    int avSepX = 0;
    int avSepY = 0;
    int numNeighbours = 0;

    for (int i = 0; i < NUMBER_OF_FISHES; i++){
        if (fishes[i] != *this && fishes[i].alive){
            double distance = distanceToFish(fishes[i]);
            if (distance < SEPARATION) {
                    avSepX += (PosX - fishes[i].PosX);
                    avSepY += (PosY - fishes[i].PosY);
            }

            else if (distance < PERCEPTION_RADIUS){
                avVelX += fishes[i].VelX;
                avVelY += fishes[i].VelY;
                avPosX += fishes[i].PosX;
                avPosY += fishes[i].PosY;
                numNeighbours += 1;
            }
        }
    }
    if (numNeighbours > 0){
        avVelX /= numNeighbours;
        avVelY /= numNeighbours;
        avPosX /= numNeighbours;
        avPosY /= numNeighbours;

        VelX += (VelX +
             (avPosX - PosX) * centeringFactor + 
             (avVelX - VelX) * matchingFactor);
        VelY += (VelY +
             (avPosY - PosY) * centeringFactor + 
             (avVelY - VelY) * matchingFactor);
    }

    VelX = VelX + (avSepX * avoidFactor);
    VelY = VelY + (avSepY * avoidFactor);

    double distToPlayer = distanceToPlayer(playerPos);

    if (distToPlayer < DISTANCE_TO_PLAYER) {
        if (distToPlayer < DISTANCE_TO_DEATH){
            Mix_PlayChannel(-1, gBite, 0);
            alive = false;
        }
        else{
            VelX += (PosX - playerPos.x) * avoidFactor * 2;
            VelY += (PosY - playerPos.y) * avoidFactor * 2;
        }

    }

    double speed = sqrt(pow(VelX,2) + pow(VelY,2));

    VelX = (VelX/speed) * velocity;
    VelY = (VelY/speed) * velocity;

    angleRad = atan2(VelY, VelX); 

    move();
}
