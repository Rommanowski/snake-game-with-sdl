#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"

#include "../classes/classes.h"

// Deklaracja funkcji

void cap_framerate( Uint32 starting_tick);

void handleCorners( Sprite *head, int *x_move, int *y_move );

int handleKeys( int *x_move, int *y_move, bool *running, SDL_Event event, Sprite *head );

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);

#endif