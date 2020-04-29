#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

class Rectangle {
    private:
        int _x;
        int _y;
        int _width;
        int _height;

    public:
        Rectangle() {}
        Rectangle(int x, int y, int width, int height):
        _x(x),
        _y(y),
        _width(width),
        _height(height) {}

        const int get_center_x() const { return this->_x + this->_width / 2; }
        const int get_center_y() const { return this->_y + this->_height / 2; }
        const int get_left() const { return this->_x; }
        const int get_right() const { return this->_x + this->_width; }
        const int get_top() const { return this->_y; }
        const int get_bottom() const { return this->_y + this->_height; }
        const int get_width() const {return this->_width; }
        const int get_height() const {return this->_height; }

        const int get_side(sides::Side side) const {
            return
                side == sides::TOP ? this->get_top():
                side == sides::BOTTOM ? this->get_bottom():
                side == sides::RIGHT ? this->get_right():
                side == sides::LEFT ? this->get_left():
                sides::NONE;
        }

        const bool collides_with(const Rectangle& other) const {
            return
                this->get_right() >= other.get_left() &&
                this->get_left() <= other.get_right() &&
                this->get_top() <= other.get_bottom() &&
                this->get_bottom() >= other.get_top();
        }

        const bool is_valid_rectangle() const {
            return
                this->_x >= 0 && this->_y >= 0 &&
                this->_width >= 0 && this->_height >= 0;
        }
};

#endif