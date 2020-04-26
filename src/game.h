#ifndef GAME_H
#define GAME_H

#include "sprite.h"

class Graphics;

class Game {
    private:
        void game_loop();
        void update (double elapsed_time);
        void draw (Graphics& graphics);
        Sprite _player;
    public:
        Game();
        ~Game();
};

#endif