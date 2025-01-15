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

void handleCorners( Sprite *head, int *x_move, int *y_move )
{
// jesli idzie w lewo i trafi na lewa krawedz
    if( ( *x_move == -1 ) && ( head->x_pos == 0 ) ){
        // jesli jest na gornej krawedzi, nie moze isc w swoje prawo
        if( head->y_pos == 0){
            *x_move = 0;
            *y_move = 1;
            head->direction = DOWN;
        }
        else{
            *x_move = 0;
            *y_move = -1;
            head->direction = UP;
        }

    }
    // idzie w prawo i prawa kwawedz
    if( ( *x_move == 1 ) && ( head->x_pos == X_BORDER - 1 ) ){
        if( head->y_pos == Y_BORDER - 1){
            *x_move = 0;
            *y_move = -1;
            head->direction = UP;
        }
        else{
            *x_move = 0;
            *y_move = 1;
            head->direction = DOWN;
        }
    }
    // idzie w gore i gorna krawedz
    if( ( *y_move == -1 ) && ( head->y_pos == 0 ) ){
        if( head->x_pos == X_BORDER - 1){
            *x_move = -1;
            *y_move = 0;
            head->direction = LEFT;
        }
        else{
            *x_move = 1;
            *y_move = 0;
            head->direction = RIGHT;
        }
    }
    // idzie w dol i dolna krawedz
    if( ( *y_move == 1 ) && ( head->y_pos == Y_BORDER - 1 ) ){
        if( head->x_pos == 0){
            *x_move = 1;
            *y_move = 0;
            head->direction = RIGHT;
        }
        else{
            *x_move = -1;
            *y_move = 0;
            head->direction = LEFT;
        }
    }
}

int handleKeys( int *x_move, int *y_move, bool *running, SDL_Event event, Sprite *head ){

    if( ( event.type == SDL_QUIT ) || ( event.key.keysym.sym == SDLK_ESCAPE )){
        *running = 0;
        printf("ESCAPE! \n");
        return 1;
    }

    if( event.type == SDL_KEYDOWN ){

        switch(event.key.keysym.sym){
            case SDLK_s:
                if( head->direction == UP ) break;
                if( head->y_pos == Y_BORDER - 1 ) break;           // the second if statement is to prevent snake running into itself on borders
                *y_move = 1;
                *x_move = 0;
                head->direction = DOWN;
                break;
            case SDLK_w:
                if( head->direction == DOWN ) break;
                if( head->y_pos == 0 ) break;
                *y_move = -1;
                *x_move = 0;
                head->direction = UP;
                break;
            case SDLK_a:
                if( head->direction == RIGHT ) break;
                if( head->x_pos == 0 ) break;
                *y_move = 0;
                *x_move = -1;
                head->direction = LEFT;
                break;
            case SDLK_d:
                if( head->direction == LEFT ) break;
                if( head->x_pos == X_BORDER - 1 ) break;
                *y_move = 0;
                *x_move = 1;
                head->direction = RIGHT;
                break;
        }
    }
    return 0;
}


// narysowanie napisu txt na powierzchni screen, zaczynaj�c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj�ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		}
	}


