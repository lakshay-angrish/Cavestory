#ifndef SLOPE_H
#define SLOPE_H

#include "globals.h"
#include "rectangle.h"
#include <cmath>

class Slope {
    private:
        Vector2 _p1;
        Vector2 _p2;
        double _slope;
    public:
        Slope() {}
        Slope(Vector2 p1, Vector2 p2):
        _p1(p1),
        _p2(p2) {
            if (this->_p2.x - this->_p1.x != 0) {
                this->_slope = (fabs(this->_p2.y) - fabs(this->_p1.y)) / (fabs(this->_p2.x) - fabs(this->_p1.x));
            }
        }

        const inline double get_slope() const{
            return this->_slope;
        }

        const inline Vector2 get_p1() const{
            return this->_p1;
        }

        const inline Vector2 get_p2() const{
            return this->_p2;
        }

        const bool collides_with(const Rectangle &other) const {
            return
                (other.get_right() >= this->_p2.x &&
                other.get_left() <= this->_p1.x &&
                other.get_top() <= this->_p2.y &&
                other.get_bottom() >= this->_p1.y) ||

                (other.get_right() >= this->_p1.x &&
                other.get_left() <= this->_p2.x &&
                other.get_top() <= this->_p1.y &&
                other.get_bottom() >= this->_p2.y) ||

                (other.get_left() <= this->_p1.x &&
                other.get_right() >= this->_p2.x &&
                other.get_top() <= this->_p1.y &&
                other.get_bottom() >= this->_p2.y) ||

                (other.get_left() <= this->_p2.x &&
                other.get_right() >= this->_p1.x &&
                other.get_top() <= this->_p2.y &&
                other.get_bottom() >= this->_p1.y);
        }
};

#endif