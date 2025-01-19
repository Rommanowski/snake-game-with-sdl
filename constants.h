#ifndef CONSTANTS_H
#define CONSTANTS_H

#define _USE_MATH_DEFINES
#include <math.h>

// Macro genereting random numbers between a and b
#define RANDOM(a, b) ((a) + rand() % ((b) - (a) + 1))   

// constants
#define PLAYER_SIZE 25      // dimensions of a square that snake is made of. Should be at least 25, since bitmaps that make dots are 25x25 pixels
#define DOT_SIZE 25         // should always be 25!!!   beacause bitmaps that make dots are 25x25 pixels

#define Y_BORDER 15         // game area dimension, measured in squares
#define X_BORDER 20

#define SCREEN_WIDTH ( ( X_BORDER * PLAYER_SIZE ) + ( 2 * EDGE ))	// screen width and height in pixels
#define SCREEN_HEIGHT ( ( Y_BORDER * PLAYER_SIZE) + ( 3 * EDGE ))	
#define INFO_HEIGHT 100        // height of info panel on top

#define EDGE 10                // size of grey edges
#define LETTER_SIZE 8          // constant - should be 8 - to read letters from cs8x8.bmp

#define CENTER_TEXT(text) \
    ((SCREEN_WIDTH - strlen(text) * LETTER_SIZE) / 2)       // this is for calculating X at which text should start so it's in the middle

#define FPS 50      // frames per seconds
#define SPEED_UPDATE_INTERVAL (5 * 1000)       // how fast speed changes (in miliseconds)
#define INITIAL_MOVE_INTERVAL 250              // miliseconds between each move at start
#define MIN_MOVE_INTERVAL 25                   // snake cannot move faster than that
#define SPEED_INCREASE_FACTOR 1.2              // move interval is being divided by that at speedup
#define SPEED_REDUCTION_FACTOR 1.4             // move interval is being multiplied by that if red dot is colected
#define MIN_REDDOT_INTERVAL 3 * 1000           // red dot waits at least this many miliseconds to show up again
#define MAX_REDDOT_INTERVAL 10 * 1000          // analogically

#define SNAKE_STARING_SIZE 3                   // snake is this many squares long at start
#define SNAKE_START_X 3
#define SNAKE_START_Y 3


// just to tell directions apart in more readable form
#define UP -1
#define RIGHT 2
#define DOWN 1
#define LEFT -2


#endif // CONSTANTS_H
