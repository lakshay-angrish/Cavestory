#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include "tile.h"
#include "rectangle.h"
#include <string>
#include <vector>

class Graphics;
struct SDL_Texture;
struct Tileset;

class Level {
    private:
        std::string _map_name;
        Vector2 _spawn_point;
        Vector2 _size;
        Vector2 _tile_size;
        SDL_Texture* background_texture;

        std::vector<Tile> _tile_list;
        std::vector<Tileset> _tilesets;
        std::vector<Rectangle> _collision_rects;

        void load_map(std::string map_name, Graphics& graphics);

    public:
        Level();
        Level(std::string map_name, Vector2 spawn_point, Graphics& graphics);
        ~Level();
        void update(int elapsed_time);
        void draw(Graphics& graphics);

        std::vector<Rectangle> check_tile_collisions(const Rectangle& other);
        const Vector2 get_player_spawn_point() const;
};

struct Tileset {
    SDL_Texture* Texture;
    int first_gid;
    Tileset() {
        this->first_gid = -1;
    }
    Tileset(SDL_Texture* texture, int first_gid) {
        this->first_gid = first_gid;
        this->Texture = texture;
    }
};


#endif