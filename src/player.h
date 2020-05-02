#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include "slope.h"
#include "door.h"
#include "level.h"
#include "enemy.h"

namespace player_constants {
    const double WALK_SPEED = 0.2;
    const double JUMP_SPEED = 0.7;
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
        bool _looking_up;
        bool _looking_down;

        int _max_health;
        int _current_health;

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
        void jump();

        void look_up();
        void look_down();
        void stop_looking_up();
        void stop_looking_down();

        const double get_x() const;
        const double get_y() const;

        const int get_max_health() const { return this->_max_health; }
        const int get_current_health() const { return this->_current_health; }

        void handle_tile_collisions(std::vector<Rectangle>& others);
        void handle_slope_collisions(std::vector<Slope>& others);
        void handle_door_collision(std::vector<Door>& others, Level& level, Graphics& graphics);
        void handle_enemy_collisions(std::vector<Enemy*>& others);

        void gain_health(int amount);
};

#endif