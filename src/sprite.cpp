#include "sprite.h"
#include "graphics.h"
#include "globals.h"

#include <iostream>
#include <vector>
#include <algorithm>

Sprite::Sprite() {}

Sprite::Sprite(Graphics& graphics, const std::string path, int source_x, int source_y, int width, int height, double x_pos, double y_pos): _x(x_pos), _y(y_pos) {

    this->_source_rect.x = source_x;
    this->_source_rect.y = source_y;
    this->_source_rect.w = width;
    this->_source_rect.h = height;

    this->_sprite_sheet = SDL_CreateTextureFromSurface(graphics.get_renderer(), graphics.load_image(path));
    if (this->_sprite_sheet == NULL) {
        std::cerr << "Error loading Sprites\n";
        exit(1);
    }

    this->_bounding_box = Rectangle(this->_x, this->_y, width * globals::SPRITE_SCALE,
        height * globals::SPRITE_SCALE);
}

Sprite::~Sprite() {}

void Sprite::draw (Graphics& graphics, int x, int y) {
    SDL_Rect destination_rect = {
        x, y, this->_source_rect.w * globals::SPRITE_SCALE, this->_source_rect.h * globals::SPRITE_SCALE
    };

    graphics.blit_surface(this->_sprite_sheet, &this->_source_rect, &destination_rect);
}

void Sprite::update() {
    this->_bounding_box = Rectangle(this->_x, this->_y, this->_source_rect.w * globals::SPRITE_SCALE,
        this->_source_rect.h * globals::SPRITE_SCALE);
}

const Rectangle Sprite::get_bounding_box() const {
    return this->_bounding_box;
}

const sides::Side Sprite::get_collision_side(const Rectangle &other) const {
    int amt_right = abs(this->get_bounding_box().get_right() - other.get_left());
    int amt_left = abs(this->get_bounding_box().get_left() - other.get_right());
    int amt_top = abs(this->get_bounding_box().get_top() - other.get_bottom());
    int amt_bottom = abs(this->get_bounding_box().get_bottom() - other.get_top());

    std::vector<int> diffs = {
        amt_top,
        amt_bottom,
        amt_right,
        amt_left
    };

    int lowest = *(std::min_element(diffs.begin(), diffs.end()));

    return
        lowest == amt_right ? sides::RIGHT:
        lowest == amt_left ? sides::LEFT:
        lowest == amt_top ? sides::TOP:
        lowest == amt_bottom ? sides::BOTTOM:
        sides::NONE;
}