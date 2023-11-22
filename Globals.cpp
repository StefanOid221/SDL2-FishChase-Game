#include "Globals.h"
#include "LTexture.h"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

Mix_Chunk* gBite = nullptr;

//Scene textures
LTexture gPlayerTexture;
LTexture gFishTexture;
