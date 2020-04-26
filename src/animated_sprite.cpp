#include "animated_sprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics& graphics, std::string path, int source_x, int source_y, int width, int height, double x_pos, double y_pos, double time_to_update):
    Sprite(graphics, path, source_x, source_y, width, height, x_pos, y_pos),
    _frame_index(0),
    _elapsed_time(0),
    _time_to_update(time_to_update),
    _visible(true),
    _current_animation_once(false),
    _current_animation("") {}

void AnimatedSprite::add_animation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
    std::vector<SDL_Rect> rectangles;
    for (int i = 0; i < frames; i++) {
        SDL_Rect rect = { (i + x) * width, y, width, height };
        rectangles.push_back(rect);
    }

    this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
    this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::reset_animation() {
    this->_animations.clear();
    this->_offsets.clear();
}

void AnimatedSprite::play_animation(std::string animation, bool once) {
    this->_current_animation_once = once;
    if (this->_current_animation != animation) {
        this->_current_animation = animation;
        this->_frame_index = 0;
    }
}

void AnimatedSprite::set_visible(bool visible) {
    this->_visible = visible;
}

void AnimatedSprite::stop_animation() {
    this->_frame_index = 0;
    this->animation_done(this->_current_animation);
}

void AnimatedSprite::update(int elapsed_time) {
    Sprite::update();
    this->_elapsed_time += elapsed_time;

    if (this->_elapsed_time > this->_time_to_update) {
        this->_elapsed_time -= this->_time_to_update;
        if (this->_frame_index < this->_animations[this->_current_animation].size() - 1) {
            this->_frame_index++;

        } else {
            if (this->_current_animation_once == true) {
                this->set_visible(false);
            }
            this->stop_animation();
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y) {
    if (this->_visible) {
        SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offsets[this->_current_animation].x;
		destinationRectangle.y = y + this->_offsets[this->_current_animation].y;
		destinationRectangle.w = this->_source_rect.w * globals::SPRITE_SCALE;
		destinationRectangle.h = this->_source_rect.h * globals::SPRITE_SCALE;

		SDL_Rect sourceRect = this->_animations[this->_current_animation][this->_frame_index];
		graphics.blit_surface(this->_sprite_sheet, &sourceRect, &destinationRectangle);
    }
}

void AnimatedSprite::animation_done(std::string current_animation) {

}

void AnimatedSprite::setup_animation() {
    this->add_animation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
    this->add_animation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}
