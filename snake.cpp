#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

extern "C" {
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

#define PLAYER_SIZE 25      // jeden kwadrat, z ktorego sklada sie waz ma wymiary 25x25 pikseli

#define Y_BORDER ( SCREEN_HEIGHT / PLAYER_SIZE )        // wymiary mapy, liczone w kwadratach
#define X_BORDER ( SCREEN_WIDTH / PLAYER_SIZE )

#define SCREEN_WIDTH	670
#define SCREEN_HEIGHT	920

#define BORDER 10
#define FPS 10


using namespace std;

void cap_framerate( Uint32 starting_tick)
{
    if( ( 1000/FPS) > ( SDL_GetTicks() - starting_tick ) )
        {
            SDL_Delay( 1000/FPS - (SDL_GetTicks() - starting_tick) );
        }
}
// lol
class Sprite{
    
    protected:
        SDL_Surface *image;
        SDL_Rect rect;

        int origin_x, origin_y;

    public:

        int x_pos, y_pos;

        Sprite( Uint32 color, int x, int y, int w = PLAYER_SIZE, int h = PLAYER_SIZE )
        {

            image = SDL_CreateRGBSurface( 0, w, h, 32, 0, 0, 0, 0);

            SDL_FillRect( image, NULL, color);

            rect = image->clip_rect;

            rect.x = x * PLAYER_SIZE + BORDER;
            rect.y = y * PLAYER_SIZE + BORDER;

            x_pos = x;
            y_pos = y;

        }


        void update()   // can be overriden
        {

        }

        void move(int y_move, int x_move){

            rect.x += x_move * PLAYER_SIZE;
            rect.y += y_move * PLAYER_SIZE;

            x_pos += x_move;
            y_pos += y_move;

        }
        
        void draw( SDL_Surface *destination)
        {
            SDL_BlitSurface( image, NULL, destination, &rect );
        }

        SDL_Surface* get_image( ) const{
            return image;
        }

        bool operator==( const Sprite &other ) const{
            return ( image == other.get_image() );
        }
};

class Background : public Sprite{

    public: 
        Background( Uint32 color, int x, int y, int w, int h):
        Sprite( color, x, y, w, h )
        {

            image = SDL_CreateRGBSurface( 0, w, h, 32, 0, 0, 0, 0);

            SDL_FillRect( image, NULL, color);

            rect = image->clip_rect;

            rect.x = x;
            rect.y = y;

        }
};

class Block : public Sprite{

    public:
        Block( Uint32 color, int x, int y, int w = 48, int h = 48 ) : 
        Sprite ( color, x, y, w, h ){

            update_properties();

        }

	int x_pos, y_pos;
	int x_dir, y_dir;

    void update_properties(){
        origin_x = 0;
        origin_y = 0;

        set_position( rect.x, rect.y );
    }

    void set_position( int x, int y){
        rect.x = x; // - origin_x;
        rect.y = y; // - origin_y;
    }

};

int mainLoop(){


	return 0;
}
int main(){
    SDL_Init( SDL_INIT_EVERYTHING);
    SDL_Window *window = NULL;

    window = SDL_CreateWindow( "Wafel! <3",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                0 );
    if(window == nullptr)
    {
        cout << "There was an error initializing the window! " << endl 
             << SDL_GetError() << endl;
    }

    SDL_Surface *screen = SDL_GetWindowSurface( window );

	// obwodka dookola
    Uint32 gray = SDL_MapRGB( screen->format, 100, 100, 100);
	SDL_FillRect( screen, NULL, gray);

	Uint32 grass = SDL_MapRGB( screen-> format, 50, 50, 100);

    Uint32 green = SDL_MapRGB( screen->format, 50, 255, 50);
    Sprite object_green( green, 0, 0);

	// tlo, po ktorym porusza sie waz
    Background background( grass, BORDER, BORDER, SCREEN_WIDTH - ( 2 * BORDER ), SCREEN_HEIGHT - (2 * BORDER ) );
    background.draw( screen );

    SDL_UpdateWindowSurface( window );

    SDL_Event event;
    bool running = 1;
    int iter = 0;

    int x_move = 1, y_move = 0;

    while(running)
    {
		Uint32 starting_tick = SDL_GetTicks();

        while( SDL_PollEvent(&event))
        {

            if( ( event.type == SDL_QUIT ) || ( event.key.keysym.sym == SDLK_ESCAPE )){
                running = 0;
				printf("ESCAPE! \n");
                break;
            }

			if( event.type == SDL_KEYDOWN ){

				switch(event.key.keysym.sym){
					case SDLK_DOWN:
						y_move = 1;
                        x_move = 0;
						break;
					case SDLK_UP:
						y_move = -1;
                        x_move = 0;
						break;
					case SDLK_LEFT:
						y_move = 0;
                        x_move = -1;
						break;
					case SDLK_RIGHT:
						y_move = 0;
                        x_move = 1;
						break;
			    }
			
			}

			// tutaj bedzie obsluga eventow

        }

		cap_framerate(starting_tick);
		Uint32 current_time = SDL_GetTicks() - starting_tick;
		printf("frame time: %d ms (should be: %d ms) \n", current_time, 1000/FPS);

        // jesli idzie w lewo i trafi na lewa krawedz
        if( ( x_move == -1 ) && ( object_green.x_pos == 0 ) ){
            // jesli jest na gornej krawedzi, nie moze isc w swoje prawo
            if( object_green.y_pos == 0){
                x_move = 0;
                y_move = 1;
            }
            else{
                x_move = 0;
                y_move = -1;
            }

        }
        // idzie w prawo i prawa kwawedz
        if( ( x_move == 1 ) && ( object_green.x_pos == X_BORDER - 1 ) ){
            if( object_green.y_pos == Y_BORDER - 1){
                x_move = 0;
                y_move = -1;
            }
            else{
                x_move = 0;
                y_move = 1;
            }
        }
        // idzie w gore i gorna krawedz
        if( ( y_move == -1 ) && ( object_green.y_pos == 0 ) ){
            if( object_green.x_pos == X_BORDER - 1){
                x_move = -1;
                y_move = 0;
                printf("DEBUG \n");
            }
            else{
                x_move = 1;
                y_move = 0;
            }
        }
        // idzie w dol i dolna krawedz
        if( ( y_move == 1 ) && ( object_green.y_pos == Y_BORDER - 1 ) ){
            if( object_green.x_pos == 0){
                x_move = 1;
                y_move = 0;
            }
            else{
                x_move = -1;
                y_move = 0;
            }
        }

        object_green.move( y_move, x_move );

        background.draw( screen );
        object_green.draw( screen );
		SDL_UpdateWindowSurface( window );

    }
 
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}