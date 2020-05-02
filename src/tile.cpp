#include "tile.h"

Tile::Tile() {}

Tile::Tile(SDL_Texture *tileset, Vector2 size, Vector2 tileset_position, Vector2 position):
_tileset(tileset),
_size(size),
_tileset_position(tileset_position),
_position(Vector2(position.x * globals::SPRITE_SCALE, position.y * globals::SPRITE_SCALE)) {}

void Tile::update(int elapsed_time) {

}

void Tile::draw(Graphics& graphics) {
    SDL_Rect destination_rect = {
        this->_position.x,
        this->_position.y,
        int(this->_size.x * globals::SPRITE_SCALE),
        int(this->_size.y * globals::SPRITE_SCALE)
    };
    SDL_Rect source_rect = {
        this->_tileset_position.x,
        this->_tileset_position.y,
        this->_size.x,
        this->_size.y
    };
    graphics.blit_surface(this->_tileset, &source_rect, &destination_rect);
}