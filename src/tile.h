#ifndef TILE_H
#define TILE_H

#include "globals.h"
#include "graphics.h"

class Tile {
    protected:
        SDL_Texture* _tileset;
        Vector2 _size;
        Vector2 _tileset_position;
        Vector2 _position;

    public:
        Tile();
        Tile(SDL_Texture* tileset, Vector2 size, Vector2 tileset_position, Vector2 position);
        void update(int elapsed_time);
        void draw(Graphics& graphics);
};

#endif