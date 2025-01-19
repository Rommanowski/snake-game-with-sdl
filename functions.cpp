#include "functions.h"
#include "constants.h"
#include "classes.h"
#include <stdio.h>
#include <string.h>

void cap_framerate( Uint32 starting_tick, int offset )
{
    if( ( 1000/FPS) > ( SDL_GetTicks() - starting_tick - offset ) )
        {
            SDL_Delay( 1000/FPS - (SDL_GetTicks() - starting_tick - offset ) );
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

int handleKeys( int *x_move, int *y_move, SDL_Event event, Sprite *head ){

    if( ( event.type == SDL_QUIT ) || ( event.key.keysym.sym == SDLK_ESCAPE )){
        return 1;
    }

    if( event.type == SDL_KEYDOWN ){

        switch(event.key.keysym.sym){
            // down
            case SDLK_s:
                if( head->direction == UP ) break;
                if( head->y_pos == Y_BORDER - 1 ) break;           // the second if statement is to prevent snake running into itself on borders
                if( head->last_move_direction == UP ) break;
                *y_move = 1;
                *x_move = 0;
                head->direction = DOWN;
                break;
            // up
            case SDLK_w:
                if( head->direction == DOWN ) break;
                if( head->y_pos == 0 ) break;
                if( head->last_move_direction == DOWN ) break;
                *y_move = -1;
                *x_move = 0;
                head->direction = UP;
                break;
            // left
            case SDLK_a:
                if( head->direction == RIGHT ) break;
                if( head->x_pos == 0 ) break;
                if( head->last_move_direction == RIGHT ) break;
                *y_move = 0;
                *x_move = -1;
                head->direction = LEFT;
                break;
            // right
            case SDLK_d:
                if( head->direction == LEFT ) break;
                if( head->x_pos == X_BORDER - 1 ) break;
                if( head->last_move_direction == LEFT ) break;
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

int gameOver( Sprite *head, Uint32 color, SDL_Surface *screen, SDL_Surface *charset, SDL_Window *window, Snake *snake, SDL_Event event ){

    head = new Sprite( color, head->x_pos, head->y_pos);
    head->draw( screen );
    SDL_UpdateWindowSurface( window );
    SDL_Delay( 750 );

    char text1[1000], text2[1000], text3[1000], text4[1000];
    sprintf(text1, "                            ");
    sprintf(text2, "    GAME OVER! SCORE: %d    ", snake->score);
    sprintf(text3, " 'n' - new game, ESC - quit ");
    sprintf(text4, "                            ");
    DrawString( screen, CENTER_TEXT(text1), SCREEN_HEIGHT/2 - 16, text1, charset );
    DrawString( screen, CENTER_TEXT(text2), SCREEN_HEIGHT/2 - 8, text2, charset );
    DrawString( screen, CENTER_TEXT(text3), SCREEN_HEIGHT/2 - 0, text3, charset );
    DrawString( screen, CENTER_TEXT(text4), SCREEN_HEIGHT/2 + 8, text4, charset );

    SDL_UpdateWindowSurface( window );
    SDL_Delay( 1000 );

    while( true )
    {
        while (SDL_PollEvent( &event ) ){
            if( event.key.keysym.sym == SDLK_n)
            {
                return 0;

            }
            else if( event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT )
            {
                return 1;
            }
        }
    }
}

void restartGame( Snake **snake, Sprite *head, Apple *apple, int *x_move,
                  int *y_move, bool *restart, Uint32 green, int *timer_offset ){

    (*snake)->removeTail( );
    head->x_pos = 4;
    head->y_pos = 4;
    *x_move = 1;
    *y_move = 0;
    head->setPosition( );
    head->last_move_direction = RIGHT;
    head->direction = RIGHT;
    *snake = new Snake( head );
    for( int i = 0; i < SNAKE_STARING_SIZE - 1; ++i ) (*snake)->lengthen( green );
    apple->findPosition( (*snake) );
    *restart = true;
    *timer_offset = SDL_GetTicks( );
}

void displayStaticInfo(SDL_Surface* screen, SDL_Surface* charset) {
    char personal_info[1000], requirements[1000];
    sprintf(personal_info, " ---Jakub Romanowski s203681--- ");
    sprintf(requirements, " requirements:: 1,2,3,4 A,B,C,D ");
    DrawString(screen, CENTER_TEXT(personal_info), 25, personal_info, charset);
    DrawString(screen, CENTER_TEXT(requirements), 35, requirements, charset);
}

void loadResources(SDL_Surface*& charset) {
    charset = SDL_LoadBMP("cs8x8.bmp");
    if (charset == NULL) {
        printf("Error with loading the cs8x8.bmp charset!\n");
        SDL_Quit();
        exit(1);
    }
}

void initializeWindow(SDL_Window*& window, SDL_Surface*& screen) {
    window = SDL_CreateWindow( "Wafel! <3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT + INFO_HEIGHT, 0);
    if (window == nullptr) {
        printf("There was an error initializing the window! \n");
        SDL_Quit();
        exit(1);
    }
    screen = SDL_GetWindowSurface(window);
}

void initColorPalette( SDL_Surface *screen, Uint32 *gray, Uint32 *grass, Uint32 *green, Uint32 *red, Uint32 *blue, Uint32 *brown, Uint32 *aqua ){
    *gray = SDL_MapRGB( screen->format, 100, 100, 100);
	*grass = SDL_MapRGB( screen-> format, 50, 100, 50);
    *green = SDL_MapRGB( screen->format, 50, 255, 50);
    *red = SDL_MapRGB( screen->format, 255, 50, 50);
    *blue = SDL_MapRGB( screen->format, 100, 150, 255);
    *brown = SDL_MapRGB( screen->format, 150, 75, 0);
    *aqua = SDL_MapRGB( screen->format, 173, 216, 230);
}

void handleSnakeSpeed( Snake *snake, int starting_tick ){
    if( snake->last_speed_update + SPEED_UPDATE_INTERVAL <= starting_tick ){

        snake->last_speed_update = starting_tick;
        snake->speedUp( );
    }
}

void displayDynamicInfo( Snake *snake, int starting_tick, SDL_Surface *screen, SDL_Surface *charset ){
    char game_info[1000];
    sprintf(game_info, " Pts: %d  time: %.2f  speed: %.1f  len: %d ",
            snake->score, float( starting_tick)  / 1000, float( 1000 ) / snake->move_interval, snake->getSize( ) );
    DrawString( screen, CENTER_TEXT(game_info), 50, game_info, charset );
}

void drawStuff( SDL_Surface *screen, Sprite *background, Snake *snake, Apple *apple, RedDot *dot ){

        background->draw( screen );
        snake->drawAll( screen );
        apple->draw( screen );
        dot->displayDot( snake, screen );

}


