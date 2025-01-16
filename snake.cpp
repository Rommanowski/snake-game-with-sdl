#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdlib> 
#include <ctime>

extern "C" {
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

#include "constants/constants.h"
#include "classes/classes.h"
#include "functions/functions.h"

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

    SDL_Surface *screen = SDL_GetWindowSurface( window );

    char personal_info[1000];
    char game_info[1000];
    SDL_Surface *charset = NULL;
    charset = SDL_LoadBMP( "bitmaps/cs8x8.bmp" );
    if( charset == NULL ){
        printf("Error with loading the cs8x8.bmp charset!\n");
        SDL_FreeSurface( screen );
        SDL_FreeSurface( charset );
        SDL_Quit();
        return 1;
    }

	// colors
    Uint32 gray = SDL_MapRGB( screen->format, 100, 100, 100);
	Uint32 grass = SDL_MapRGB( screen-> format, 50, 50, 100);
    Uint32 green = SDL_MapRGB( screen->format, 50, 255, 50);
    Uint32 red = SDL_MapRGB( screen->format, 255, 50, 50);
    Uint32 blue = SDL_MapRGB( screen->format, 50, 50, 255);
    Uint32 brown = SDL_MapRGB( screen->format, 150, 75, 0);
    // colors

    // gray background
    SDL_FillRect( screen, NULL, gray);

    // SPRITES
    Sprite *head = new Sprite( green, 3, 3);

    // SNAKE
    Snake *snake = new Snake( head );

    //APPLE
    Apple apple( red, 2, 2, PLAYER_SIZE, PLAYER_SIZE);

    for(int i=0; i<8; ++i){
        snake->lengthen( green );
    }

	// tlo, po ktorym porusza sie waz
    Background background( grass, EDGE, 2 * EDGE + INFO_HEIGHT, SCREEN_WIDTH - ( 2 * EDGE ), SCREEN_HEIGHT - ( 3 * EDGE ) );
    background.draw( screen );

    Background info( brown, EDGE, EDGE, SCREEN_WIDTH - ( 2 * EDGE ), INFO_HEIGHT);
    info.draw( screen );

    sprintf(personal_info, " SNAKE GAME by --Jakub Romanowski s203681-- 2025 ");
    DrawString( screen, CENTER_TEXT(personal_info), 30, personal_info, charset );

    SDL_UpdateWindowSurface( window );

    SDL_Event event;
    bool running = 1;
    int iter = 0;
    int timer_offset = 0;

    int x_move = 1, y_move = 0;

    apple.findPosition( snake );

    while( true )
    {
		Uint32 starting_tick = SDL_GetTicks();
        bool restart = 0;

        while( SDL_PollEvent(&event))
        {
            if(event.key.keysym.sym == SDLK_n)
            {
                // snake->removeTail( );
                // head->x_pos = 4;
                // head->y_pos = 4;
                // x_move = 1;
                // y_move = 0;
                // head->setPosition( );
                // snake = new Snake( head );
                // snake->lengthen( green );
                // snake->lengthen( green );
                // apple.findPosition( snake );
                // restart = true;
                restartGame( &snake, head, apple, &x_move, &y_move, &restart, green );
                continue;
            }
            else if( handleKeys( &x_move, &y_move, event, head ) ){
                SDL_DestroyWindow( window );
                SDL_Quit();

                return 0;
            }
        }
        if( restart ){
            SDL_Delay( 750 );
            continue;
        }

		cap_framerate(starting_tick);
		Uint32 current_time = SDL_GetTicks() - starting_tick;
		//printf("frame time: %d ms (should be: %d ms) \n", current_time, 1000/FPS);

        handleCorners( head, &x_move, &y_move );

        if( snake->last_move + snake->move_interval <= starting_tick ){

            snake->move( );
            head->move( y_move, x_move );
            snake->last_move = starting_tick;

            if(snake->collision()){
                if( !gameOver( head, red, screen, charset, window, snake, event ) ){
                    restartGame( &snake, head, apple, &x_move, &y_move, &restart, green );
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
                //snake->removeTail( );
                printf("SNAKE SIZE:[%d]\n", snake->getSize());
                snake->score++;
            }

        }
     
        background.draw( screen );
        //head->draw( screen );
        snake->drawAll( screen );
        apple.draw( screen );

        sprintf(game_info, " Pts: %d     time: %.2f     snake speed: %.2f ",
                snake->score, float( starting_tick)  / 1000, float( 1000 ) / snake->move_interval );
        DrawString( screen, CENTER_TEXT(game_info), 50, game_info, charset );

		SDL_UpdateWindowSurface( window );

    }
 
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}