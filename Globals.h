#ifndef GLOBALS_H
#define GLOBALS_H

#include "LTexture.h"
#include "SDL2/SDL_mixer.h"

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Scene textures
extern LTexture gPlayerTexture;
extern LTexture gFishTexture;

extern Mix_Chunk* gBite;

#endif 