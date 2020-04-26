#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"

class Graphics;

class Game {
    private:
        void game_loop();
        void update (double elapsed_time);
        void draw (Graphics& graphics);
        Player _player;
        Level _level;
    public:
        Game();
        ~Game();
};

#endif