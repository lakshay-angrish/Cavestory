#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int window_width = 640;
const int window_height = 480;

class Graphics {
    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        std::map<std::string, SDL_Surface*> _sprite_sheets;
    public:
        Graphics();
        ~Graphics();

        SDL_Surface* load_image (const std::string& path);
        void blit_surface (SDL_Texture* texture, SDL_Rect* source_rect, SDL_Rect* destination_rect);
        void flip();
        void clear();
        SDL_Renderer* get_renderer() const;
};

#endif