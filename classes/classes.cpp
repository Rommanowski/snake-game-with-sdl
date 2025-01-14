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
    rect.y = y * PLAYER_SIZE + EDGE;
    x_pos = x;
    y_pos = y;
    next = nullptr;
}


void Sprite::move(int y_move, int x_move) {
    rect.x += x_move * PLAYER_SIZE;
    rect.y += y_move * PLAYER_SIZE;
    x_pos += x_move;
    y_pos += y_move;
}

void Sprite::setPosition( ){
    rect.x = x_pos * PLAYER_SIZE + EDGE;
    rect.y = y_pos * PLAYER_SIZE + EDGE;
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
Background::Background(Uint32 color, int x, int y, int w, int h)
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
}

int Snake::getSize( ){
    
    int snake_len = 0;
    Sprite *current = origin;

    while( current != nullptr){
        snake_len++;
        current = current->next;
    }
    return snake_len;

}

void Snake::enqueue( Sprite *to_add ){
    last->next = to_add;
    last = to_add;
}

void Snake::move( ){
    Sprite *current = origin;
    while( current != nullptr ){
        // 'pull' the next node to the previous one
        current->next->x_pos = current->x_pos;
        current->next->y_pos = current->y_pos;
        current->setPosition( );
        //printf("current: %d x %d    next: %d x %d \n", current->x_pos, current->y_pos, current->next->x_pos, current->next->y_pos);

        current = current->next;
    }
}

void Snake::drawAll( SDL_Surface* destination ){
    Sprite *current = origin;
    while( current != nullptr ){
        current->draw( destination );
        current = current->next;
    }
}
