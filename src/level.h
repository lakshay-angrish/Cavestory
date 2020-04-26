#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include <string>

class Graphics;
class SDL_Texture;

class Level {
    private:
        std::string _map_name;
        Vector2 _spawn_point;
        Vector2 _size;
        SDL_Texture* background_texture;

        void load_map(std::string map_name, Graphics& graphics);

    public:
        Level();
        Level(std::string map_name, Vector2 spawn_point, Graphics& graphics);
        ~Level();
        void update(int elapsed_time);
        void draw(Graphics& graphics);
};

#endif