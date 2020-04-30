#include "player.h"
#include "graphics.h"

Player::Player() {}

Player::Player(Graphics& graphics, Vector2 spawn_point):
AnimatedSprite(graphics, "../assets/sprites/MyChar.png", 0, 0, 16, 16, spawn_point.x, spawn_point.y, 100),
_dx(0),
_dy(0),
_facing(RIGHT),
_grounded(false) {

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

const double Player::get_x() const {
    return this->_x;
}

const double Player::get_y() const {
    return this->_y;
}

void Player::update(double elapsed_time) {
    if (this->_dy < player_constants::GRAVITY_CAP) {
        this->_dy += player_constants::GRAVITY * elapsed_time;
    }

    this->_y += this->_dy * elapsed_time;
    this->_x += this->_dx * elapsed_time;
    AnimatedSprite::update(elapsed_time);
}

void Player::draw(Graphics& graphics) {
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}

void Player::handle_tile_collisions(std::vector<Rectangle> &others) {
    //others contain the collision rects with whom the player has collided
    for (auto other: others) {
        sides::Side side = this->get_collision_side(other);
        switch (side) {
            case sides::TOP:
                this->_dy = 0;
                this->_y = other.get_bottom() + 1;
                if (this->_grounded) {
                    this->_dx = 0;
                    this->_x -= this->_facing == RIGHT ? 0.5 : -0.5;
                }
                break;

            case sides::BOTTOM:
                this->_y = other.get_top() - this->_bounding_box.get_height() - 1;
                this->_dy = 0;
                this->_grounded = true;
                break;

            case sides::LEFT:
                this->_x = other.get_right() + 1;
                break;

            case sides::RIGHT:
                this->_x = other.get_left() - this->_bounding_box.get_width() - 1;
                break;

            default:    break;
        }
    }
}

void Player::handle_slope_collisions(std::vector<Slope> &others) {
    for (auto other: others) {
        //y = mx + b
        int b = other.get_p1().y - (other.get_slope() * fabs(other.get_p1().x));
        int center_x = this->_bounding_box.get_center_x();
        int new_y = (other.get_slope() * center_x) + b - 8;

        if (this->_grounded) {
            this->_y = new_y - this->_bounding_box.get_height();
            this->_grounded = true;
        }
    }
}