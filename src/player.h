#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"

namespace player_constants {
    const double WALK_SPEED = 0.2;
}

class Graphics;

class Player: public AnimatedSprite {
    private:
    double _dx;
    double _dy;
    Direction _facing;

    public:
        Player();
        Player(Graphics& graphics, double x, double y);
        void draw(Graphics& graphics);
        void update(double elapsed_time);

        virtual void animation_done(const std::string current_animation);
        virtual void setup_animation();

        void move_left();
        void move_right();
        void stop_moving();
};

#endif