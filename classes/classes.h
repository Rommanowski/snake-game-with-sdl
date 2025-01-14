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

        int x_pos, y_pos;

        Sprite( Uint32 color, int x, int y, int w = PLAYER_SIZE, int h = PLAYER_SIZE );


        virtual void update();   // can be overriden

        void move(int y_move, int x_move);
        
        void draw( SDL_Surface *destination);

        SDL_Surface* get_image( ) const;

        bool operator==( const Sprite &other ) const;
};


class Background : public Sprite{

    public: 
        Background( Uint32 color, int x, int y, int w, int h);
};

class Block : public Sprite{

    public:
        Block( Uint32 color, int x, int y, int w = 48, int h = 48 );

	int x_pos, y_pos;
	int x_dir, y_dir;

    void update_properties();

    void set_position( int x, int y);

};

#endif