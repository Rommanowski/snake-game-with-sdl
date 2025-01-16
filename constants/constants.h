#ifndef CONSTANTS_H
#define CONSTANTS_H

#define _USE_MATH_DEFINES
#include <math.h>

// Makro
#define RANDOM(a, b) ((a) + rand() % ((b) - (a) + 1)) 

// Stałe dla programu
#define PLAYER_SIZE 25      // jeden kwadrat, z ktorego sklada sie waz ma wymiary 25x25 pikseli

#define Y_BORDER 20         // wymiary mapy, liczone w kwadratach
#define X_BORDER 20

#define SCREEN_WIDTH ( ( X_BORDER * PLAYER_SIZE ) + ( 2 * EDGE ))	//670
#define SCREEN_HEIGHT ( ( Y_BORDER * PLAYER_SIZE) + ( 3 * EDGE ))	//920
#define INFO_HEIGHT 100        // jak duży jest panel z informacjami na dole

#define EDGE 10
#define LETTER_SIZE 8

#define CENTER_TEXT(text) \
    ((SCREEN_WIDTH - strlen(text) * LETTER_SIZE) / 2)

#define FPS 50
#define SPEED_UPDATE_INTERVAL (10 * 1000)       // speed changes every 10 seconds
#define INITIAL_MOVE_INTERVAL 300
#define MIN_MOVE_INTERVAL 50


// kierunki, w których zwrócona jest głowa węża. Wartości nie mają większego znaczenia, chodzi o rozróżnienie ich
#define UP -1
#define RIGHT 2
#define DOWN 1
#define LEFT -2


#endif // CONSTANTS_H
