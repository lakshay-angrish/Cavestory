#ifndef ANIMATED_TILE_H
#define ANIMATED_TILE_H

#include "tile.h"

#include <vector>

class AnimatedTile: public Tile {
    private:
        std::vector<Vector2> _tileset_positions;
        int _tile_to_draw;
        int _duration;

    protected:
        int _amount_of_time;
        bool _not_done;

    public:
        AnimatedTile(std::vector<Vector2> tileset_positions, int duration, SDL_Texture* tileset, Vector2 size, Vector2 position);

        void draw(Graphics& graphics);
        void update(int elapsed_time);
};

struct AnimatedTileInfo {
    public:
        std::vector<int> tile_ids;
        int duration;
        int tilesets_first_gid;
        int start_tile_id;
};

#endif