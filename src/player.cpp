#include "player.h"
#include "graphics.h"

Player::Player() {}

Player::Player(Graphics& graphics, Vector2 spawn_point):
AnimatedSprite(graphics, "../assets/sprites/MyChar.png", 0, 0, 16, 16, spawn_point.x, spawn_point.y, 100),
_dx(0),
_dy(0),
_facing(RIGHT),
_grounded(false),
_looking_down(false),
_looking_up(false),
_max_health(3),
_current_health(3) {

    graphics.load_image("../assets/sprites/MyChar.png");
    this->setup_animation();
    this->play_animation("IdleRight");
}

void Player::setup_animation() {
    this->add_animation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
    this->add_animation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
    this->add_animation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
    this->add_animation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));

    this->add_animation(1, 3, 0, "IdleLeftUp", 16, 16, Vector2(0, 0));
    this->add_animation(1, 3, 16, "IdleRightUp", 16, 16, Vector2(0, 0));
    this->add_animation(3, 3, 0, "RunLeftUp", 16, 16, Vector2(0, 0));
    this->add_animation(3, 3, 16, "RunRightUp", 16, 16, Vector2(0, 0));

    this->add_animation(1, 6, 0, "LookDownLeft", 16, 16, Vector2(0, 0));
    this->add_animation(1, 6, 16, "LookDownRight", 16, 16, Vector2(0, 0));

    this->add_animation(1, 7, 0, "LookBackwardsLeft", 16, 16, Vector2(0, 0));
    this->add_animation(1, 7, 16, "LookBackwardsRight", 16, 16, Vector2(0, 0));
}

void Player::move_left() {
    if (this->_looking_down && this->_grounded)
        return;

    this->_dx = -player_constants::WALK_SPEED;
    this->_facing = LEFT;

    if (!this->_looking_up)
        this->play_animation("RunLeft");
}

void Player::move_right() {
    if (this->_looking_down && this->_grounded)
        return;

    this->_dx = player_constants::WALK_SPEED;
    this->_facing = RIGHT;

    if (!this->_looking_up)
        this->play_animation("RunRight");
}

void Player::stop_moving() {
    this->_dx = 0;

    if (!this->_looking_up && !this->_looking_down)
        this->play_animation(this->_facing == LEFT ? "IdleLeft" : "IdleRight");
}

void Player::look_up() {
    this->_looking_up = true;
    if (this->_dx == 0)
        this->play_animation(this->_facing == LEFT ? "IdleLeftUp" : "IdleRightUp");
    else
        this->play_animation(this->_facing == LEFT ? "RunLeftUp" : "RunRightUp");
}

void Player::stop_looking_up() {
    this->_looking_up = false;
}

void Player::look_down() {
    this->_looking_down = true;
    if (this->_grounded)
        this->play_animation(this->_facing == LEFT ? "LookBackwardsLeft" : "LookBackwardsRight");
    else
        this->play_animation(this->_facing == LEFT ? "LookDownLeft" : "LookDownLeft");
}

void Player::stop_looking_down() {
    this->_looking_down = false;
}

void Player::jump() {
	if (this->_grounded) {
		this->_dy = 0;
		this->_dy -= player_constants::JUMP_SPEED;
		this->_grounded = false;
	}
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

void Player::handle_door_collision(std::vector<Door> &others, Level& level, Graphics& graphics) {
    for (int i = 0; i != others.size(); i++) {
        if (this->_looking_down && this->_grounded) {
            level = Level(others[i].get_destination(), graphics);
            this->_x = level.get_player_spawn_point().x;
            this->_y = level.get_player_spawn_point().y;
        }
    }
}

void Player::handle_enemy_collisions(std::vector<Enemy*> &others) {
    for (auto other: others) {
        other->touch_player(this);
    }
}

void Player::gain_health(int amount) {
    this->_current_health += amount;
}