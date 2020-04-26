#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include <string>

class Graphics;

class Player: public AnimatedSprite {
    public:
        Player();
        Player(Graphics& graphics, double x, double y);
        void draw(Graphics& graphics);
        void update(double elapsed_time);

        virtual void animation_done(const std::string current_animation);
        virtual void setup_animation();
};

#endif