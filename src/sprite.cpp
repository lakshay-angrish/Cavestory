#include "sprite.h"
#include "graphics.h"

#include <iostream>

Sprite::Sprite() {}

Sprite::Sprite(Graphics& graphics, const std::string path, int source_x, int source_y, int width, int height, double x_pos, double y_pos): _x(x_pos), _y(y_pos) {

    this->_source_rect->x = source_x;
    this->_source_rect->y = source_y;
    this->_source_rect->w = width;
    this->_source_rect->h = height;

    this->_sprite_sheet = SDL_CreateTextureFromSurface(graphics.get_renderer(), graphics.load_image(path));
    if (this->_sprite_sheet == NULL) {
        std::cerr << "Error loading Sprites\n";
        exit(1);
    }
}

Sprite::~Sprite() {}

void Sprite::draw (Graphics& graphics, int x, int y) {
    SDL_Rect destination_rect = {
        x, y, this->_source_rect->w, this->_source_rect->h
    };

    graphics.blit_surface(this->_sprite_sheet, this->_source_rect, &destination_rect);
}

void Sprite::update() {}