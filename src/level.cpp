#include "level.h"
#include "graphics.h"

Level::Level() {}

Level::Level(std::string map_name, Vector2 spawn_point, Graphics& graphics):
_map_name(map_name),
_spawn_point(spawn_point),
_size(Vector2()) {

    this->load_map(map_name, graphics);
}

Level::~Level() {}

void Level::load_map(std::string map_name, Graphics &graphics) {
    this->background_texture = SDL_CreateTextureFromSurface(graphics.get_renderer(), graphics.load_image("../assets/backgrounds/bkBlue.png"));
    this->_size = Vector2(1280, 960);
}

void Level::update(int elapsed_time) {

}

void Level::draw(Graphics &graphics) {
    SDL_Rect source_rect = { 0, 0, 64, 64 };
    SDL_Rect destination_rect;

    for (int i = 0; i != this->_size.x / 64; i++) {
        for (int j = 0; j != this->_size.y / 64; j++) {
            destination_rect.x = i * 64;
            destination_rect.y = j * 64;
            destination_rect.w = 64;
            destination_rect.h = 64;
            graphics.blit_surface(this->background_texture, &source_rect, &destination_rect);
        }
    }
}