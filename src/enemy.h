#ifndef ENEMY_H
#define ENEMY_H

#include "animated_sprite.h"
#include "globals.h"
#include "player.h"

#include <string>

class Graphics;

class Enemy: public AnimatedSprite {
    protected:
        Direction _direction;
        int _max_health;
        int _current_health;

    public:
        Enemy(Graphics& graphics, std::string path, int source_x, int source_y, int width, int height, Vector2 spawn_point, double time_to_update);

        const int get_max_health() const { return this->_max_health; }
        const int get_current_health() const { return this->_current_health; }

        virtual void update(int elapsed_time, Player& player);
        virtual void draw(Graphics& graphics);

        virtual void touch_player(Player* player) = 0;
};

#endif