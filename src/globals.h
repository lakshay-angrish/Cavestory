#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const double SPRITE_SCALE = 2.0;
}

namespace sides {
    enum Side {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };

    inline Side get_opposite_side(Side side) {
        return
            side == TOP ? BOTTOM:
            side == BOTTOM ? TOP:
            side == RIGHT ? LEFT:
            side == LEFT ? RIGHT:
            NONE;
    }
}

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Vector2 {
    public:
        int x;
        int y;
        Vector2(): x(0), y(0) {}
        Vector2(int x, int y): x(x), y(y) {}
        Vector2 zero() {
            return Vector2();
        }
};

#endif