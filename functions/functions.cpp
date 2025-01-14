#include "functions.h"
#include "../constants/constants.h"
#include "../classes/classes.h"
#include <stdio.h>

void cap_framerate( Uint32 starting_tick)
{
    if( ( 1000/FPS) > ( SDL_GetTicks() - starting_tick ) )
        {
            SDL_Delay( 1000/FPS - (SDL_GetTicks() - starting_tick) );
        }
}

void handleCorners( Sprite head, int *x_move, int *y_move )
{
// jesli idzie w lewo i trafi na lewa krawedz
    if( ( *x_move == -1 ) && ( head.x_pos == 0 ) ){
        // jesli jest na gornej krawedzi, nie moze isc w swoje prawo
        if( head.y_pos == 0){
            *x_move = 0;
            *y_move = 1;
        }
        else{
            *x_move = 0;
            *y_move = -1;
        }

    }
    // idzie w prawo i prawa kwawedz
    if( ( *x_move == 1 ) && ( head.x_pos == X_BORDER - 1 ) ){
        if( head.y_pos == Y_BORDER - 1){
            *x_move = 0;
            *y_move = -1;
        }
        else{
            *x_move = 0;
            *y_move = 1;
        }
    }
    // idzie w gore i gorna krawedz
    if( ( *y_move == -1 ) && ( head.y_pos == 0 ) ){
        if( head.x_pos == X_BORDER - 1){
            *x_move = -1;
            *y_move = 0;
            printf("DEBUG \n");
        }
        else{
            *x_move = 1;
            *y_move = 0;
        }
    }
    // idzie w dol i dolna krawedz
    if( ( *y_move == 1 ) && ( head.y_pos == Y_BORDER - 1 ) ){
        if( head.x_pos == 0){
            *x_move = 1;
            *y_move = 0;
        }
        else{
            *x_move = -1;
            *y_move = 0;
        }
    }
}

int handleKeys( int *x_move, int *y_move, bool *running, SDL_Event event){

    if( ( event.type == SDL_QUIT ) || ( event.key.keysym.sym == SDLK_ESCAPE )){
        *running = 0;
        printf("ESCAPE! \n");
        return 1;
    }

    if( event.type == SDL_KEYDOWN ){

        switch(event.key.keysym.sym){
            case SDLK_s:
                *y_move = 1;
                *x_move = 0;
                break;
            case SDLK_w:
                *y_move = -1;
                *x_move = 0;
                break;
            case SDLK_a:
                *y_move = 0;
                *x_move = -1;
                break;
            case SDLK_d:
                *y_move = 0;
                *x_move = 1;
                break;
        }
    }
    return 0;
}