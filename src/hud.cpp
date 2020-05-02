#include "hud.h"

HUD::HUD() {}

HUD::HUD(Graphics& graphics, Player& player) {
    this->_player = player;
    this->_healthbar_sprite = Sprite(graphics, "../assets/sprites/TextBox.png", 0, 40, 64, 8, 35, 70);
    this->_health_number1 = Sprite(graphics, "../assets/sprites/TextBox.png", 0, 56, 8, 8, 66, 70);
    this->_current_healthbar = Sprite(graphics, "../assets/sprites/TextBox.png", 0, 25, 39, 5, 83, 72);
    this->_lvl_word = Sprite(graphics, "../assets/sprites/TextBox.png", 81, 81, 11, 7, 38, 55);
    this->_lvl_number = Sprite(graphics, "../assets/sprites/TextBox.png", 0, 56, 8, 8, 66, 52);
    this->_exp_bar = Sprite(graphics, "../assets/sprites/TextBox.png", 0, 72, 40, 8, 83, 52);
    this->_slash = Sprite(graphics, "../assets/sprites/TextBox.png", 72, 48, 8, 8, 100, 36);
    this->_dashes = Sprite(graphics, "../assets/sprites/TextBox.png", 81, 51, 15, 11, 132, 26);
}

void HUD::update(int elapsed_time) {
    this->_health_number1.set_source_rect_x(8 * this->_player.get_current_health());

    //calculate health bar width
    double num = (double)(this->_player.get_current_health()) / (double)(this->_player.get_max_health());
    this->_current_healthbar.set_source_rect_width(std::floor(num * 39));
}

void HUD::draw(Graphics& graphics) {
    this->_healthbar_sprite.draw(graphics, this->_healthbar_sprite.get_x(), this->_healthbar_sprite.get_y());
    this->_health_number1.draw(graphics, this->_health_number1.get_x(), this->_health_number1.get_y());
    this->_current_healthbar.draw(graphics, this->_current_healthbar.get_x(), this->_current_healthbar.get_y());
    this->_lvl_word.draw(graphics, this->_lvl_word.get_x(), this->_lvl_word.get_y());
    this->_lvl_number.draw(graphics, this->_lvl_number.get_x(), this->_lvl_number.get_y());
    this->_exp_bar.draw(graphics, this->_exp_bar.get_x(), this->_exp_bar.get_y());
    this->_slash.draw(graphics, this->_slash.get_x(), this->_slash.get_y());
    this->_dashes.draw(graphics, this->_dashes.get_x(), this->_dashes.get_y());
}