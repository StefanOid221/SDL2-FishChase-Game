#include "Util.h"
#include "Player.h"
#include "Fish.h"
#include "Globals.h"
#include <iostream>


int main( int argc, char *argv[] ){
    if (!init())
    {
        printf( "Failed to initialize!%s\n", SDL_GetError());
    }
    else
    {
        if (!loadMedia()){
            printf( "Failed to initialize!%s\n", SDL_GetError());
        }
        else{
            bool quit = false;
            SDL_Event e;
            Player player;
            Fish fishes[NUMBER_OF_FISHES];
            spawnFishes(player, fishes);
            
            while (!quit)
            {
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    player.handleEvent(&e);
				}
                SDL_RenderClear( gRenderer );
                player.move();
                for (int i=0; i< NUMBER_OF_FISHES; i++){
                    fishes[i].updateFlock(fishes, player.getPosition());
                    fishes[i].render();
                }
                player.render();
                SDL_RenderPresent( gRenderer );

            }
        }
    }
    close();
    // std::cout << "Press Enter to exit...";    
    // std::cin.get(); 

	return 0;
}