#include "graphics.h"
#include "globals.h"

Graphics::Graphics () {
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Cavestory");
}

Graphics::~Graphics () {
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::load_image (const std::string& path) {
    if (this->_sprite_sheets.count(path) == 0) {
        this->_sprite_sheets[path] = IMG_Load(path.c_str());
    }
    return this->_sprite_sheets[path];
}

void Graphics::blit_surface (SDL_Texture* texture, SDL_Rect* source_rect, SDL_Rect* destination_rect) {
    SDL_RenderCopy(this->_renderer, texture, source_rect, destination_rect);
}

void Graphics::flip() {
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::get_renderer() const {
    return this->_renderer;
}