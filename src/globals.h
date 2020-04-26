#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const double SPRITE_SCALE = 2.0;
}

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