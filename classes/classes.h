#ifndef CLASSES_H
#define CLASSES_H
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"

#include "../constants/constants.h"

// Deklaracja klas

class Sprite{
    
    protected:
        SDL_Surface *image;
        SDL_Rect rect;
        int origin_x, origin_y;

    public:
        int direction;  // up, down, right, left
        int x_pos, y_pos;
        Sprite *next;
        Sprite *prev;

        Sprite( Uint32 color, int x = 0, int y = 0 , int w = PLAYER_SIZE, int h = PLAYER_SIZE );

        void move(int y_move, int x_move);

        void setPosition( );
        
        void draw( SDL_Surface *destination);

        SDL_Surface* get_image( ) const;

        bool operator==( const Sprite &other ) const;
};


class Background : public Sprite{

    public: 
        Background( Uint32 color, int x, int y, int w, int h);
};

class Snake{

    private:

    public:
        // constructor
        Snake(Sprite *origin);

        Sprite *origin;
        Sprite *last;

        int move_interval;
        int last_move;

        int getSize( );
        Sprite *getLast( );
        void enqueue( Sprite *to_add );
        void dequeue( );
        void move( );
        void drawAll( SDL_Surface* destination );
        void lengthen( Uint32 color );
        bool collision( );
};


#endif