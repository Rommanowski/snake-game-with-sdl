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

int main(){
    SDL_Init( SDL_INIT_EVERYTHING);
    // init the window
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

	// colors
    Uint32 gray = SDL_MapRGB( screen->format, 100, 100, 100);
	Uint32 grass = SDL_MapRGB( screen-> format, 50, 50, 100);
    Uint32 green = SDL_MapRGB( screen->format, 50, 255, 50);
    Uint32 red = SDL_MapRGB( screen->format, 255, 50, 50);
    Uint32 blue = SDL_MapRGB( screen->format, 50, 50, 255);
    // colors

    // gray background
    SDL_FillRect( screen, NULL, gray);

    // SPRITES
    Sprite head( green, 5, 5);
    Sprite tail( green, 5, 4);
    Sprite grzechotka( red, 5, 3);
    Sprite grzechotka2( blue, 5, 3);

    // SNAKE
    Snake Snake( &head );
    Snake.enqueue( &tail );
    Snake.enqueue( &grzechotka);
    Snake.enqueue( &grzechotka2 );

	// tlo, po ktorym porusza sie waz
    Background background( grass, EDGE, EDGE, SCREEN_WIDTH - ( 2 * EDGE ), SCREEN_HEIGHT - (2 * EDGE ) );
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
            handleKeys( &x_move, &y_move, &running, event);
        }

		cap_framerate(starting_tick);
		Uint32 current_time = SDL_GetTicks() - starting_tick;
		//printf("frame time: %d ms (should be: %d ms) \n", current_time, 1000/FPS);

        handleCorners(head, &x_move, &y_move);

        Snake.move( );
        head.move( y_move, x_move );

        background.draw( screen );
        head.draw( screen );
        Snake.drawAll( screen );
		SDL_UpdateWindowSurface( window );

    }
 
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}