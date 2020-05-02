#ifndef BAT_H
#define BAT_H

#include "enemy.h"

class Bat: public Enemy {
    private:
        bool _should_move_up;
        double _starting_x;
        double _starting_y;

    public:
        Bat(Graphics& graphics, Vector2 spawn_point);
        void update(int elapsed_time, Player& player);
        void draw(Graphics& graphics);

        void animation_done(std::string current_animation);
        void setup_animation();

        void touch_player(Player* player);
};

#endif