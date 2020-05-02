#ifndef HUD_H
#define HUD_H

#include "sprite.h"
#include "graphics.h"
#include "player.h"

class HUD {
    private:
        Player _player;
        Sprite _healthbar_sprite;
        Sprite _health_number1;
        Sprite _current_healthbar;

        Sprite _lvl_word;
        Sprite _lvl_number;
        Sprite _exp_bar;

        Sprite _slash;
        Sprite _dashes;

    public:
        HUD();
        HUD(Graphics& graphics, Player& player);

        void update(int elapsed_time, Player& player);
        void draw(Graphics& graphics);
};

#endif