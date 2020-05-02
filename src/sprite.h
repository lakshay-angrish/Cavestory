#ifndef SPRITE_H
#define SPRITE_H

#include "rectangle.h"
#include <string>
#include <SDL2/SDL.h>

class Graphics;

class Sprite {
    protected:
        SDL_Texture* _sprite_sheet;
        SDL_Rect _source_rect;
        double _x;
        double _y;
        Rectangle _bounding_box;

    public:
        // source_x/y -- (x, y) of sprite in the sprite sheet
        // width/height -- of sprite
        // pos -- where to draw
        Sprite();
        Sprite(Graphics& graphics, const std::string path, int source_x, int source_y, int width, int height, double x_pos, double y_pos);
        virtual ~Sprite();
        virtual void update();
        void draw (Graphics& graphics, int x, int y);

        const Rectangle get_bounding_box() const;
        const sides::Side get_collision_side(const Rectangle& other) const;

        const double get_x() const { return this->_x; }
        const double get_y() const { return this->_y; }

        void set_source_rect_x(int value);
        void set_source_rect_y(int value);

        void set_source_rect_width(int value);
        void set_source_rect_height(int value);

};

#endif