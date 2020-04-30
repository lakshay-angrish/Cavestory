#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include "slope.h"

namespace player_constants {
    const double WALK_SPEED = 0.2;
    const double GRAVITY = 0.002;
    const double GRAVITY_CAP = 0.8;
}

class Graphics;

class Player: public AnimatedSprite {
    private:
    double _dx;
    double _dy;
    Direction _facing;

    bool _grounded;

    public:
        Player();
        Player(Graphics& graphics, Vector2 spawn_point);
        void draw(Graphics& graphics);
        void update(double elapsed_time);

        virtual void animation_done(const std::string current_animation);
        virtual void setup_animation();

        void move_left();
        void move_right();
        void stop_moving();

        const double get_x() const;
        const double get_y() const;

        void handle_tile_collisions(std::vector<Rectangle>& others);
        void handle_slope_collisions(std::vector<Slope>& others);
};

#endif