#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"

#include <map>

class Input {
    private:
        std::map<SDL_Scancode, bool> _held_keys;
        std::map<SDL_Scancode, bool> _pressed_keys;
        std::map<SDL_Scancode, bool> _released_keys;
    public:
        void begin_new_frame();
        void key_up_event (const SDL_Event& event);
        void key_down_event (const SDL_Event& event);

        bool was_key_pressed (SDL_Scancode key);
        bool was_key_released (SDL_Scancode key);
        bool is_key_held (SDL_Scancode key);
};

#endif