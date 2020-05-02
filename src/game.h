#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"
#include "hud.h"
#include "graphics.h"

class Game {
    private:
        void game_loop();
        void update (double elapsed_time);
        void draw (Graphics& graphics);
        Player _player;
        Level _level;
        HUD _hud;
        Graphics _graphics;

    public:
        Game();
        ~Game();
};

#endif