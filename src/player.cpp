#include "player.h"
#include "graphics.h"

Player::Player() {}

Player::Player(Graphics& graphics, double x, double y):
AnimatedSprite(graphics, "../assets/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100) {

    graphics.load_image("../assets/sprites/MyChar.png");
    this->setup_animation();
    this->play_animation("RunRight");
}

void Player::setup_animation() {
    this->add_animation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
    this->add_animation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
    this->add_animation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
    this->add_animation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}

void Player::move_left() {
    this->_dx = -player_constants::WALK_SPEED;
    this->_facing = LEFT;
    this->play_animation("RunLeft");
}

void Player::move_right() {
    this->_dx = player_constants::WALK_SPEED;
    this->_facing = RIGHT;
    this->play_animation("RunRight");
}

void Player::stop_moving() {
    this->_dx = 0;
    this->play_animation(this->_facing == LEFT ? "IdleLeft" : "IdleRight");
}

void Player::animation_done(const std::string current_animation) {}

void Player::update(double elapsed_time) {
    this->_x += this->_dx * elapsed_time;
    AnimatedSprite::update(elapsed_time);
}

void Player::draw(Graphics& graphics) {
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}