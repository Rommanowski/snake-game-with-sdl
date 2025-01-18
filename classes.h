#ifndef CLASSES_H
#define CLASSES_H
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"

#include "constants.h"

// Deklaracja klas

class Sprite{
    
    protected:
        SDL_Surface *image;
        SDL_Rect rect;
        int origin_x, origin_y;

    public:
        int direction;  // up, down, right, left
        int x_pos, y_pos;
        int last_move_direction;
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
        int last_speed_update;

        int score;

        int getSize( );
        Sprite *getLast( );
        void enqueue( Sprite *to_add );
        void dequeue( );
        void removeTail( );
        void move( );
        void drawAll( SDL_Surface* destination );
        void lengthen( Uint32 color );
        bool collision( );
        void speedUp( );
        bool isSnake( int x_pos, int y_pos );
};

class Apple : public Sprite{

    public:
        Apple( Uint32 color, int x, int y, int w, int h);
        void findPosition( Snake *Snake );
};

class RedDot : public Apple{

    public:
        RedDot( Uint32 color );
        int time_left;
        bool visible;
        int time_to_show_up;
        
        void displayDot( Snake *snake, SDL_Surface *screen );
};

class Bar{
    
    protected:
        SDL_Surface *image;
        SDL_Rect rect;
        int origin_x, origin_y;

    public:
        int direction;  // up, down, right, left
        // int x_pos, y_pos;

        Bar( Uint32 color, int x, int y, int w, int h );

        void draw( SDL_Surface *destination);

};


#endif