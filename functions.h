#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"

#include "classes.h"

// Deklaracja funkcji

void cap_framerate( Uint32 starting_tick, int offset);

void handleCorners( Sprite *head, int *x_move, int *y_move );

int handleKeys( int *x_move, int *y_move, SDL_Event event, Sprite *head );

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);

int gameOver( Sprite *head, Uint32 color, SDL_Surface *screen, SDL_Surface *charset, SDL_Window *window, Snake *snake, SDL_Event event );

void restartGame( Snake **snake, Sprite *head, Apple apple, int *x_move,
                  int *y_move, bool *restart, Uint32 green, int *timer_offset );

#endif