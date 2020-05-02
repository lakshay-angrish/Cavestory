#ifndef DOOR_H
#define DOOR_H

#include "rectangle.h"

#include <string>

class Door: public Rectangle  {
    private:
        std::string _destination;

    public:
        Door(Rectangle rect, std::string destination):
        Rectangle(rect.get_left() * globals::SPRITE_SCALE, rect.get_top() * globals::SPRITE_SCALE, rect.get_width() * globals::SPRITE_SCALE, rect.get_height() * globals::SPRITE_SCALE),
        _destination(destination) {}

        const Rectangle get_rectangle() const { return this->get_rect(); }
        const std::string get_destination() const { return this->_destination; }
};

#endif