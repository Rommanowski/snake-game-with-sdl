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

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define FPS 1

using namespace std;

void cap_framerate( Uint32 starting_tick)
{
    if( ( 1000/FPS) > SDL_GetTicks() - starting_tick)
        {
            SDL_Delay( 1000/FPS - (SDL_GetTicks() - starting_tick) );
        }
}
class Sprite{
    
    private:
        SDL_Surface *image;
        SDL_Rect rect;

        int origin_x, origin_y;

    public:
        Sprite( Uint32 color, int x, int y, int w = 48, int h = 48 )
        {
            image = SDL_CreateRGBSurface( 0, w, h, 32, 0, 0, 0, 0);

            SDL_FillRect( image, NULL, color);

            rect = image->clip_rect;

            origin_x = rect.w/2;
            origin_y = rect.h/2;

            rect.x = x - origin_x;
            rect.y = y - origin_y;
        }

        void update()   // can be overriden
        {

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

class SpriteGroup{

    private:

        vector<Sprite*> sprites;
        int sprites_size;

    public:

        SpriteGroup copy(){
            SpriteGroup new_group;

            for( int i=0; i < sprites_size; ++i){
                new_group.add( sprites[i]);
            }
            return new_group;
        }

        void add( Sprite *sprite ){
            sprites.push_back(sprite);
            sprites_size = sprites.size();
        }

        void remove( Sprite sprite_object ){

            for(int i=0; i<sprites_size; ++i){
                if ( *sprites[i] == sprite_object ){
                    sprites.erase( sprites.begin() + i );
                }
            }

            sprites_size = sprites.size();
        }

        bool has( Sprite sprite_object ){
            for(int i=0; i<sprites_size; ++i){
                if ( *sprites[i] == sprite_object ){
                    return true;
                }
            }
            
            return false;
        }

        void update( ){
            if(!sprites.empty()){
                for(int i=0; i<sprites_size; ++i){
                    sprites[i]->update();
                }
            }
            
        }

        void draw( SDL_Surface *destination ){
            if(!sprites.empty()){
                for(int i=0; i<sprites_size; ++i){
                    sprites[i]->draw( destination );
                }
            }
            
        }

        void empty( ){

            sprites.clear();
            sprites_size = sprites.size();

        }

        int size(){
            return sprites_size;
        }

        vector <Sprite*> get_sprites(){
            return sprites;
        }

};

int main(){
    SDL_Init( SDL_INIT_EVERYTHING);
    SDL_Window *window = NULL;

    window = SDL_CreateWindow( "Wafel! <3",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_RESIZABLE );
    if(window == nullptr)
    {
        cout << "There was an error initializing the window! " << endl 
             << SDL_GetError() << endl;
    }

    SDL_Surface *screen = SDL_GetWindowSurface( window );

    Uint32 gray = SDL_MapRGB( screen->format, 100, 100, 100);
    Uint32 red = SDL_MapRGB( screen->format, 255, 50, 50);
    Uint32 green = SDL_MapRGB( screen->format, 50, 255, 50);
    Uint32 blue = SDL_MapRGB( screen->format, 50, 50, 255);

    SDL_FillRect( screen, NULL, gray);

    Sprite object_red( red, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );
    Sprite object_green( green, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 100, 500, 5);
    Sprite object_blue( blue, SCREEN_WIDTH/2 + 100, SCREEN_HEIGHT/2 + 100);



    SpriteGroup active_sprites;
    active_sprites.add( &object_red );
    active_sprites.add( &object_green );
    active_sprites.add( &object_blue );

    active_sprites.remove( object_green );


    SDL_UpdateWindowSurface( window );

    SDL_Event event;
    bool running = 1;
    int iter = 0;
    while(running)
    {
        Uint32 starting_tick = SDL_GetTicks();

        while( SDL_PollEvent(&event))
        {
            if( event.type == SDL_QUIT){
                running = 0;
                break;
            }
        }

        cap_framerate(starting_tick);
        active_sprites.draw( screen );
        SDL_UpdateWindowSurface( window );
        object_green.draw( screen );
    }
 
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}