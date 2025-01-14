#include <stdio.h>
#include <iostream>

extern "C" {
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

#include "constants/constants.h"
#include "classes/classes.h"
#include "functions/functions.h"

using namespace std;

void cap_framerate( Uint32 starting_tick)
{
    if( ( 1000/FPS) > ( SDL_GetTicks() - starting_tick ) )
        {
            SDL_Delay( 1000/FPS - (SDL_GetTicks() - starting_tick) );
        }
}


int main(){
    SDL_Init( SDL_INIT_EVERYTHING);
    SDL_Window *window = NULL;

    window = SDL_CreateWindow( "Wafel! <3",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                0 );
    if(window == nullptr)
    {
        cout << "There was an error initializing the window! " << endl 
             << SDL_GetError() << endl;
    }

    SDL_Surface *screen = SDL_GetWindowSurface( window );

	// obwodka dookola
    Uint32 gray = SDL_MapRGB( screen->format, 100, 100, 100);
	SDL_FillRect( screen, NULL, gray);

	Uint32 grass = SDL_MapRGB( screen-> format, 50, 50, 100);

    Uint32 green = SDL_MapRGB( screen->format, 50, 255, 50);
    Sprite head( green, 0, 0);

	// tlo, po ktorym porusza sie waz
    Background background( grass, BORDER, BORDER, SCREEN_WIDTH - ( 2 * BORDER ), SCREEN_HEIGHT - (2 * BORDER ) );
    background.draw( screen );

    SDL_UpdateWindowSurface( window );

    SDL_Event event;
    bool running = 1;
    int iter = 0;

    int x_move = 1, y_move = 0;

    while(running)
    {
		Uint32 starting_tick = SDL_GetTicks();

        while( SDL_PollEvent(&event))
        {

            if( ( event.type == SDL_QUIT ) || ( event.key.keysym.sym == SDLK_ESCAPE )){
                running = 0;
				printf("ESCAPE! \n");
                break;
            }

			if( event.type == SDL_KEYDOWN ){

				switch(event.key.keysym.sym){
					case SDLK_DOWN:
						y_move = 1;
                        x_move = 0;
						break;
					case SDLK_UP:
						y_move = -1;
                        x_move = 0;
						break;
					case SDLK_LEFT:
						y_move = 0;
                        x_move = -1;
						break;
					case SDLK_RIGHT:
						y_move = 0;
                        x_move = 1;
						break;
			    }
			
			}

			// tutaj bedzie obsluga eventow

        }

		cap_framerate(starting_tick);
		Uint32 current_time = SDL_GetTicks() - starting_tick;
		printf("frame time: %d ms (should be: %d ms) \n", current_time, 1000/FPS);

        handleCorners(head, &x_move, &y_move);

        head.move( y_move, x_move );

        background.draw( screen );
        head.draw( screen );
		SDL_UpdateWindowSurface( window );

    }
 
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}