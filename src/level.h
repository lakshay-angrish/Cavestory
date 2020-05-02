#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include "tile.h"
#include "rectangle.h"
#include "door.h"
#include "slope.h"
#include "animated_tile.h"

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
        std::vector<Slope> _slopes;

        std::vector<AnimatedTile> _animated_tile_list;
        std::vector<AnimatedTileInfo> _animated_tile_infos;

        std::vector<Door> _doors;

        void load_map(std::string map_name, Graphics& graphics);
        Vector2 get_tileset_position(Tileset tls, int gid, int tile_width, int tile_height);

    public:
        Level();
        Level(std::string map_name, Graphics& graphics);
        ~Level();
        void update(int elapsed_time);
        void draw(Graphics& graphics);

        std::vector<Rectangle> check_tile_collisions(const Rectangle& other);
        std::vector<Slope> check_slope_collisions(const Rectangle& other);
        std::vector<Door> check_door_collisions(const Rectangle& other);
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