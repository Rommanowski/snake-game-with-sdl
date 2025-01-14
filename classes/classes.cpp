#include "classes.h"
#include "../constants/constants.h"

// Implementation for Sprite
Sprite::Sprite(Uint32 color, int x, int y, int w, int h) {
    image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(image, NULL, color);
    rect = image->clip_rect;
    rect.x = x * PLAYER_SIZE + BORDER;
    rect.y = y * PLAYER_SIZE + BORDER;
    x_pos = x;
    y_pos = y;
}

void Sprite::update() {
    // Can be overridden by derived classes
}

void Sprite::move(int y_move, int x_move) {
    rect.x += x_move * PLAYER_SIZE;
    rect.y += y_move * PLAYER_SIZE;
    x_pos += x_move;
    y_pos += y_move;
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

// Implementation for Block
Block::Block(Uint32 color, int x, int y, int w, int h)
    : Sprite(color, x, y, w, h) {
    update_properties();
}

void Block::update_properties() {
    origin_x = 0;
    origin_y = 0;
    set_position(rect.x, rect.y);
}

void Block::set_position(int x, int y) {
    rect.x = x; // - origin_x;
    rect.y = y; // - origin_y;
}
