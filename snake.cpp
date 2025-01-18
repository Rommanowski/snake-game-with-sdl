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
    window = SDL_CreateWindow( "Wafel! <3",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT + INFO_HEIGHT,
                                0 );
    if(window == nullptr)
    {
        cout << "There was an error initializing the window! " << endl 
             << SDL_GetError() << endl;
    }

    // surfaces ( screen for displaying game, charset for displaying letters )
    SDL_Surface *screen = SDL_GetWindowSurface( window );
    SDL_Surface *charset = NULL;
    charset = SDL_LoadBMP( "cs8x8.bmp" );
    if( charset == NULL ){
        printf("Error with loading the cs8x8.bmp charset!\n");
        SDL_FreeSurface( screen );
        SDL_FreeSurface( charset );
        SDL_Quit();
        return 1;
    }

    // strings
    char personal_info[1000];
    char game_info[1000];
    char requirements[1000];



	// colors
    Uint32 gray = SDL_MapRGB( screen->format, 100, 100, 100);
	Uint32 grass = SDL_MapRGB( screen-> format, 50, 100, 50);
    Uint32 green = SDL_MapRGB( screen->format, 50, 255, 50);
    Uint32 red = SDL_MapRGB( screen->format, 255, 50, 50);
    Uint32 blue = SDL_MapRGB( screen->format, 100, 150, 255);
    Uint32 brown = SDL_MapRGB( screen->format, 150, 75, 0);
    Uint32 aqua = SDL_MapRGB( screen->format, 173, 216, 230);
    // colors

    // gray background
    SDL_FillRect( screen, NULL, gray);

    // the head of the snake
    Sprite *head = new Sprite( green, 3, 3);

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
    sprintf(personal_info, " ---Jakub Romanowski s203681--- ");
    sprintf(requirements, " requirements:: 1,2,3,4 A,B,C,D ");
    DrawString( screen, CENTER_TEXT(personal_info), 25, personal_info, charset );
    DrawString( screen, CENTER_TEXT(requirements), 35, requirements, charset );

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
        // restart = 0;

        while( SDL_PollEvent(&event))
        {
            if(event.key.keysym.sym == SDLK_n)
            {
                restartGame( &snake, head, apple, &x_move, &y_move, &restart, green, &timer_offset);
                //dot.findPosition( snake );
                dot = new RedDot( red );
                apple.findPosition( snake );
                background.draw( screen );
                break;
            }
            else if( handleKeys( &x_move, &y_move, event, head ) ){
                SDL_DestroyWindow( window );
                SDL_Quit();

                return 0;
            }
        }
        if( restart ) continue;

        handleCorners( head, &x_move, &y_move );

        if( snake->last_move + snake->move_interval <= starting_tick ){

            snake->move( );
            head->move( y_move, x_move );
            snake->last_move = starting_tick;

            if(snake->collision()){
                if( !gameOver( head, red, screen, charset, window, snake, event ) ){
                    restartGame( &snake, head, apple, &x_move, &y_move, &restart, green, &timer_offset );   
                    continue;
                }
                else{
                    SDL_DestroyWindow( window );
                    SDL_Quit();
                    return 0;
                }
            }

            if( snake->last_speed_update + SPEED_UPDATE_INTERVAL <= starting_tick ){

                snake->last_speed_update = starting_tick;
                snake->speedUp( );
            }

            if( ( head->x_pos == apple.x_pos ) && ( head->y_pos == apple.y_pos ) ){

                apple.findPosition( snake );
                snake->lengthen( green );
                snake->score++;
            }
        }
     
        background.draw( screen );
        snake->drawAll( screen );
        apple.draw( screen );
        dot->displayDot( snake, screen );
        

        sprintf(game_info, " Pts: %d  time: %.2f  speed: %.1f  len: %d ",
                snake->score, float( starting_tick)  / 1000, float( 1000 ) / snake->move_interval, snake->getSize( ) );
        DrawString( screen, CENTER_TEXT(game_info), 50, game_info, charset );

		SDL_UpdateWindowSurface( window );

		cap_framerate(starting_tick, timer_offset);

    }
 
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}