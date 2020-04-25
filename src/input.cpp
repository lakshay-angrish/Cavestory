#include "input.h"

void Input::begin_new_frame() {
    this->_pressed_keys.clear();
    this->_released_keys.clear();
}

void Input::key_down_event (const SDL_Event& event) {
    this->_pressed_keys[event.key.keysym.scancode] = true;
    this->_held_keys[event.key.keysym.scancode] = true;
}

void Input::key_up_event (const SDL_Event& event) {
    this->_released_keys[event.key.keysym.scancode] = true;
    this->_held_keys[event.key.keysym.scancode] = false;
}

bool Input::was_key_pressed (SDL_Scancode key) {
    return this->_pressed_keys[key];
}

bool Input::was_key_released (SDL_Scancode key) {
    return this->_released_keys[key];
}

bool Input::is_key_held (SDL_Scancode key) {
    return this->_held_keys[key];
}