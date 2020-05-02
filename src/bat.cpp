#include "bat.h"

Bat::Bat(Graphics& graphics, Vector2 spawn_point):
Enemy(graphics, "../assets/sprites/NpcCemet.png", 32, 32, 16, 16, spawn_point, 140),
_starting_x(spawn_point.x),
_starting_y(spawn_point.y),
_should_move_up(false) {
    this->setup_animation();
    this->play_animation("FlyLeft");
}

void Bat::update(int elapsed_time, Player& player) {
    this->_direction = player.get_x() > this->_x ? RIGHT : LEFT;
    this->play_animation(this->_direction == RIGHT ? "FlyRight" : "FlyLeft");

    this->_y -= this->_should_move_up ? 0.1 : -0.1;
    if (this->_y > (this->_starting_y + 20) || this->_y < (this->_starting_y - 20)) {
        this->_should_move_up = !this->_should_move_up;
    }

    Enemy::update(elapsed_time, player);
}

void Bat::draw(Graphics& graphics) {
    Enemy::draw(graphics);
}

void Bat::animation_done(std::string current_animation) {}

void Bat::setup_animation() {
    this->add_animation(3, 2, 32, "FlyLeft", 16, 16, Vector2(0, 0));
    this->add_animation(3, 2, 48, "FlyRight", 16, 16, Vector2(0, 0));
}

void Bat::touch_player(Player* player) {
    player->gain_health(-1);
}