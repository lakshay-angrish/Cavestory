#include "animated_tile.h"

AnimatedTile::AnimatedTile(std::vector<Vector2> tileset_positions, int duration, SDL_Texture *tileset, Vector2 size, Vector2 position):
Tile(tileset, size, tileset_positions[0], position),
_duration(duration),
_amount_of_time(0),
_not_done(false),
_tileset_positions(tileset_positions),
_tile_to_draw(0) {}

void AnimatedTile::update(int elapsed_time) {
    if (this->_amount_of_time <= 0) {

        if (this->_tile_to_draw == this->_tileset_positions.size() - 1) this->_tile_to_draw = 0;
        else  this->_tile_to_draw++;

        this->_amount_of_time = _duration;

    } else  {
        this->_amount_of_time -= elapsed_time;
    }

    Tile::update(elapsed_time);
}

void AnimatedTile::draw(Graphics &graphics) {
    SDL_Rect destination_rect = {
        this->_position.x,
        this->_position.y,
        int(this->_size.x * globals::SPRITE_SCALE),
        int(this->_size.y * globals::SPRITE_SCALE)
    };

    SDL_Rect source_rect = {
        this->_tileset_positions[this->_tile_to_draw].x,
        this->_tileset_positions[this->_tile_to_draw].y,
        this->_size.x,
        this->_size.y
    };

    graphics.blit_surface(this->_tileset, &source_rect, &destination_rect);
}