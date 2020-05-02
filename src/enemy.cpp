#include "enemy.h"

Enemy::Enemy(Graphics &graphics, std::__cxx11::string path, int source_x, int source_y, int width, int height, Vector2 spawn_point, double time_to_update):
AnimatedSprite(graphics, path, source_x, source_y, width, height, spawn_point.x, spawn_point.y, time_to_update),
_direction(LEFT),
_max_health(0),
_current_health() {}

void Enemy::update(int elapsed_time, Player& player) {
    AnimatedSprite::update(elapsed_time);
}

void Enemy::draw(Graphics& graphics) {
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}