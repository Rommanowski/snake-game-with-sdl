#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdlib> 
#include <ctime>

extern "C" {
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

#include "constants.h"
#include "classes.h"
#include "functions.h"

using namespace std;

int main(){
    srand(time(NULL));

    SDL_Init( SDL_INIT_EVERYTHING);

    // init the window
    SDL_Window *window = NULL;
    SDL_Surface *screen;
    initializeWindow( window, screen );

    // charset surface to display letters
    SDL_Surface *charset = NULL;
    loadResources( charset );

	// colors
    Uint32 gray, grass, green, red, blue, brown, aqua;
    initColorPalette(screen, &gray, &grass, &green, &red, &blue, &brown, &aqua );

    // gray background
    SDL_FillRect( screen, NULL, gray);

    // the head of the snake
    Sprite *head = new Sprite( green, SNAKE_START_X, SNAKE_START_Y);

    // SNAKE - collection of Sprites
    Snake *snake = new Snake( head );
    for(int i=0; i < SNAKE_STARING_SIZE-1; ++i) snake->lengthen( green );       // give snake it's starting length

    //APPLE ( apple is actually blue, and dot is the red bonus )
    Apple apple( blue, 2, 2, PLAYER_SIZE, PLAYER_SIZE);
    RedDot *dot = new RedDot( red );
    apple.findPosition( snake );    // set apple's position


	// make the background of the playable area and the panel with information on top
    Background background( grass, EDGE, 2 * EDGE + INFO_HEIGHT, SCREEN_WIDTH - ( 2 * EDGE ), SCREEN_HEIGHT - ( 3 * EDGE ) );
    Background info( brown, EDGE, EDGE, SCREEN_WIDTH - ( 2 * EDGE ), INFO_HEIGHT);
    background.draw( screen );
    info.draw( screen );

    // print some static information on top
    displayStaticInfo( screen, charset );

    // event ( used to read user input )
    SDL_Event event;

    // variables
    int timer_offset = 0;
    int x_move = 1, y_move = 0;
    bool restart = 0;

    // the main loop
    SDL_UpdateWindowSurface( window );
    while( true )
    {
		Uint32 starting_tick = SDL_GetTicks() - timer_offset;   // calculate current tick at the beginning of the loop
        // restart the game if it is desired
        if( restart ){
            SDL_Delay( 750 );
            restart = 0;
            continue;
        }

        // handle user's input
        while( SDL_PollEvent(&event))
        {
            // check if n pressed to start the new game
            if(event.key.keysym.sym == SDLK_n)
            {
                restartGame( &snake, head, &apple, &x_move, &y_move, &restart, green, &timer_offset);
                dot = new RedDot( red );
                background.draw( screen );
                break;
            }
            // handleKeys() switches snakes direction based on keys pressed, but returns 1 if user wants to quit the game
            else if( handleKeys( &x_move, &y_move, event, head ) ){ 
                SDL_DestroyWindow( window );
                SDL_Quit();
                return 0;
            }
        }
        if( restart ) continue;   // restart is being set to 1 in restartGame() function

        // change snake's direction if it is on the edge of the map
        handleCorners( head, &x_move, &y_move );

        // move the snake if enough time has passed
        if( snake->last_move + snake->move_interval <= starting_tick ){

            snake->handleMovement( starting_tick, y_move, x_move );

            if(snake->collision()){
                // gameOver() returns 1 if user wants to quit after losing the game, and 0 if they want to continue
                if( !gameOver( head, red, screen, charset, window, snake, event ) ){
                    restartGame( &snake, head, &apple, &x_move, &y_move, &restart, green, &timer_offset );   
                    continue;
                }
                else{
                    SDL_DestroyWindow( window );
                    SDL_Quit();
                    return 0;
                }
            }
            // speed the snake up if it should happen
            handleSnakeSpeed( snake, starting_tick );
            // if snake's head and apple have the same position, move the apple, lengthen the snake, update score
            apple.checkEaten( snake, screen );
        }
     
        // display the state of the game on top
        displayDynamicInfo( snake, starting_tick, screen, charset);

        // draw the snake and bonuses
        drawStuff( screen, &background, snake, &apple, dot );

        // update window and handle the framerate
		SDL_UpdateWindowSurface( window );
		cap_framerate(starting_tick, timer_offset);

    }
 
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}