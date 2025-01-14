#ifndef CONSTANTS_H
#define CONSTANTS_H

#define _USE_MATH_DEFINES
#include <math.h>

// Stałe dla programu
#define PLAYER_SIZE 25      // jeden kwadrat, z ktorego sklada sie waz ma wymiary 25x25 pikseli

#define Y_BORDER 32         // wymiary mapy, liczone w kwadratach
#define X_BORDER 25

#define SCREEN_WIDTH ( ( X_BORDER * PLAYER_SIZE ) + ( 2 * EDGE ))	//670
#define SCREEN_HEIGHT ( ( Y_BORDER * PLAYER_SIZE) + ( 2 * EDGE ))	//920

#define EDGE 10
#define FPS 10

#endif // CONSTANTS_H
