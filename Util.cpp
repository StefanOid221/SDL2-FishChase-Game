#include "Util.h"
#include "Constants.h"
#include "Globals.h"
#include "Player.h"
#include "Fish.h"
#include <cmath>
#include <random>
#include <iostream>
#include <algorithm>

using u32    = uint_least32_t; 
using engine = std::mt19937;

bool init()

{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load shark texture
	if( !gPlayerTexture.loadFromFile( "shark.png" ) )
	{
		printf( "Failed to load shark texture!%s\n", SDL_GetError() );
		success = false;
	}
	
	// //Load up texture
	if( !gFishTexture.loadFromFile( "fish.png" ) )
	{
		printf( "Failed to load up fish!\n" );
		success = false;
	}

	gBite = Mix_LoadWAV("bite.wav");
	if (gBite == nullptr){
		printf( "Failed to load up sound!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gPlayerTexture.free();
	gFishTexture.free();
	Mix_FreeChunk(gBite);
	// g0Texture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = nullptr;
	gRenderer = nullptr;
	gBite = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision(int x1, int x2, int y1, int y2){
	bool res = !((x1 + FISH_WIDTH/2 < x2 || x1 - FISH_WIDTH/2 > x2) && (y1 + FISH_HEIGTH/2 < y2 || y1 - FISH_HEIGTH/2 > y2));
	return res;
}

void spawnFishes(const Player& player, Fish (&fishes)[NUMBER_OF_FISHES]){
    Vector playerPos = player.getPosition();
    int fishX, fishY;
	std::random_device os_seed;
  	const u32 seed = os_seed();

	engine generator( seed );
  	std::uniform_int_distribution< u32 > distX( FISH_WIDTH, SCREEN_WIDTH );
  	std::uniform_int_distribution< u32 > distY( FISH_HEIGTH, SCREEN_HEIGHT );


    for (int i = 0; i < NUMBER_OF_FISHES; i++) {

        bool validPosition = false;
        while (!validPosition) {
            fishX = distX(generator);
            fishY = distY(generator);
			
            if (!checkCollision(fishX, playerPos.x, fishY, playerPos.y)) {
                bool collision = false;
                for (int j = 0; j < i; j++) {
                    if (checkCollision(fishX, fishes[j].PosX, fishY, fishes[j].PosY)) {
                        collision = true;
                        break;
                    }
                }
                if (!collision) {
                    fishes[i].PosX = fishX;
                    fishes[i].PosY = fishY;
					fishes[i].vectorNew ->x = distX(generator);
					fishes[i].vectorNew ->y = distY(generator);
					fishes[i].initVel();
                    validPosition = true;
                }
            }
        }
    }
}




