#include "classes.h"
#include "../constants/constants.h"
#include <stdlib.h>
#include <stdio.h>

// Implementation for Sprite
Sprite::Sprite(Uint32 color, int x, int y, int w, int h) {
    image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(image, NULL, color);
    rect = image->clip_rect;
    rect.x = x * PLAYER_SIZE + EDGE;
    rect.y = y * PLAYER_SIZE + ( 2 * EDGE ) + INFO_HEIGHT;
    x_pos = x;
    y_pos = y;
    next = nullptr;
    prev = nullptr;
    direction = RIGHT;
    last_move_direction = RIGHT;
}


void Sprite::move(int y_move, int x_move) {
    rect.x += x_move * PLAYER_SIZE;
    rect.y += y_move * PLAYER_SIZE;
    x_pos += x_move;
    y_pos += y_move;
    last_move_direction = direction;
}

void Sprite::setPosition( ){
    rect.x = x_pos * PLAYER_SIZE + EDGE;
    rect.y = y_pos * PLAYER_SIZE + ( 2 * EDGE ) + INFO_HEIGHT;
}

void Sprite::draw(SDL_Surface* destination) {
    SDL_BlitSurface(image, NULL, destination, &rect);
}

SDL_Surface* Sprite::get_image() const {
    return image;
}

bool Sprite::operator==(const Sprite& other) const {
    return (image == other.get_image());
}

// Implementation for Background
Background::Background(Uint32 color=0, int x=0, int y=0, int w=PLAYER_SIZE, int h=PLAYER_SIZE)
    : Sprite(color, x, y, w, h) {
    image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(image, NULL, color);
    rect = image->clip_rect;
    rect.x = x;
    rect.y = y;
}

Snake::Snake( Sprite *origin_node){
    // set the snake's origin node to the one passed in the constructor
    origin = nullptr;
    last = nullptr;

    origin = origin_node;
    last = origin_node;

    origin->last_move_direction = RIGHT;

    score = 0;

    move_interval = INITIAL_MOVE_INTERVAL;
    last_move = 0;
    last_speed_update = 0;
}

int Snake::getSize( ){
    
    int snake_len = 0;
    Sprite *current = origin;

    //printf("----------------------\n");
    while( current != nullptr){
        //printf("[%d]: %d x %d \n", snake_len+1, current->x_pos, current->y_pos);
        snake_len++;
        current = current->next;
    }
    //printf("\n-------------------\n");
    return snake_len;

}

void Snake::enqueue( Sprite *to_add ){
    to_add->prev = last;
    last->next = to_add;
    last = to_add;
}

void Snake::dequeue( ){

    if( getSize() <= 1) return;

    Sprite *new_last = last->prev;
    last = nullptr;
    free( last );
    last = new_last;
    last->next = nullptr;
}

void Snake::removeTail( ){
    
    while( getSize( ) > 1 ){
        dequeue( );
    }
}

void Snake::move( ){
    Sprite *current = last;

    while( current->prev != nullptr ){
        // 'pull' the next node to the previous one
        current->x_pos = current->prev->x_pos;
        current->y_pos = current->prev->y_pos;

        current->setPosition( );

        current = current->prev;

    }
}

void Snake::drawAll( SDL_Surface* destination ){
    Sprite *current = origin;
    while( current != nullptr ){
        current->draw( destination );
        current = current->next;
    }
}

void Snake::lengthen( Uint32 color){
    Sprite *tail = last;
    Sprite *temp = new Sprite( color, last->x_pos, last->y_pos );
    temp->x_pos = tail->x_pos;
    temp->y_pos = tail->y_pos;
    enqueue( temp );
}

bool Snake::collision( ){
    Sprite *node = origin->next;

    while( node != nullptr ){
        if( ( node->x_pos == origin->x_pos) && ( node->y_pos == origin->y_pos ))
            return true;
        node = node->next;
    }
    return false;
}

void Snake::speedUp( ){
    
    int new_interval = move_interval / 1.2;
    
    if( new_interval < MIN_MOVE_INTERVAL ){
        move_interval = MIN_MOVE_INTERVAL;
        return;
    }

    move_interval = new_interval;

}

bool Snake::isSnake( int y_pos, int x_pos ){
    Sprite *current = origin;

    while( current != nullptr){
        if( ( current->x_pos == x_pos) && ( current->y_pos == y_pos) )
            return 1;
        
        current = current->next;
    }
    return 0;
}

Apple::Apple( Uint32 color, int x, int y, int w, int h )
    : Sprite( color, x, y, w, h ){
    image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(image, NULL, color);
    rect = image->clip_rect;
    rect.x = x;
    rect.y = y;
}
void Apple::findPosition( Snake *snake ){

    int available_cords_x[X_BORDER * Y_BORDER];
    int available_cords_y[X_BORDER * Y_BORDER];
    int index=0;

    // szukamy wspolrzednych, na ktorych nie ma weza
    for( int i=0; i<Y_BORDER; ++i )     // i is for Y coordinates
    {
        for( int j=0; j < X_BORDER; ++j )   //j is for X
        {
            if( !snake->isSnake( i, j ) ){
                available_cords_y[index] = i;
                available_cords_x[index] = j;
                index++;
                //printf("index: %d   x: %d   y: %d \n", index, available_cords_x[index-1], available_cords_y[index-1]);
            }
        }
    }

    // teraz losujemy jedna z dostepnych wspolrzednych
    int random_free_index = RANDOM(1, index) -1;

    x_pos = available_cords_x[random_free_index];
    y_pos = available_cords_y[random_free_index];

    setPosition( );

    //printf("selection:  x: %d    y: %d      at index: %d \n", x_pos, y_pos, random_free_index);
    //printf("----------------------NEXT-------------------\n");
}

RedDot::RedDot( Uint32 color )
    : Apple( color, X_BORDER+2, Y_BORDER+2, PLAYER_SIZE, PLAYER_SIZE ){
        image = SDL_CreateRGBSurface(0, PLAYER_SIZE, PLAYER_SIZE, 32, 0, 0, 0, 0);
        SDL_FillRect(image, NULL, color);
        rect = image->clip_rect;
        rect.x = X_BORDER + 2;
        rect.y = Y_BORDER + 2;
        setPosition( );
        visible = false;
        time_left = 0;
        time_to_show_up = RANDOM(2 * 1000, 5 * 1000) + SDL_GetTicks( ); // pojawi sie za od X do Y sekund
    }

void RedDot::displayDot( Snake *snake, SDL_Surface *screen ){
    Sprite *head = snake->origin;
    if( SDL_GetTicks( ) >= time_to_show_up  && !visible ){
        visible = true;
        time_left = 5 * 1000;
        findPosition( snake );

    } 
    if( visible ){
        Uint32 brown = SDL_MapRGB( screen->format, 150, 75, 0);
        Uint32 white = SDL_MapRGB( screen->format, 200, 200, 200);
        Sprite *loading_bar_background = new Sprite( white, 1, -2, 100, 10);
        loading_bar_background->setPosition( );
        loading_bar_background->draw( screen );
        if( ( ( head->x_pos == x_pos ) && ( head->y_pos == y_pos ) ) || time_left <= 0 ){
            visible = false;
            time_to_show_up = RANDOM(2 * 1000, 5 * 1000) + SDL_GetTicks( );
            if( time_left > 0 ) snake->score++;
            x_pos = X_BORDER + 2;
            y_pos = Y_BORDER + 2;
            setPosition( );

            if( ( RANDOM( 1, 2 ) % 2 == 0 ) || ( snake->getSize( ) <= 4 ) ){
                snake->move_interval = snake->move_interval * 1.5;
            }
            else{
                snake->dequeue( );
                snake->dequeue( );
            }

            if( snake->move_interval > INITIAL_MOVE_INTERVAL )
                snake->move_interval = INITIAL_MOVE_INTERVAL;

        }
    }
    time_left -= 1000/FPS;
    draw( screen );
}

Bar::Bar( Uint32 color, int x = 0, int y = 0 , int w = PLAYER_SIZE, int h = PLAYER_SIZE ){
    image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(image, NULL, color);
    rect = image->clip_rect;
    rect.x = x * PLAYER_SIZE + EDGE;
    rect.y = y * PLAYER_SIZE + ( 2 * EDGE ) + INFO_HEIGHT;
    x_pos = x;
    y_pos = y;
};

void Bar::draw(SDL_Surface* destination) {
    SDL_BlitSurface(image, NULL, destination, &rect);
}

