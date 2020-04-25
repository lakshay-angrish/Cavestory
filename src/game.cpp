#include "game.h"
#include "graphics.h"
#include "input.h"

#include <SDL2/SDL.h>

// The main game loop

namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->game_loop();
}

Game::~Game() {

}

void Game::game_loop() {
    Graphics graphics;
    Input input;
    SDL_Event event;

    int LAST_UPDATE_TIME = SDL_GetTicks();
    while (true) {
        input.begin_new_frame();

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.repeat == 0) {
                    input.key_down_event(event);
                }

            } else if (event.type == SDL_KEYUP) {
                input.key_up_event(event);

            } else if (event.type == SDL_QUIT) {
                return;
            }
        }

        if (input.was_key_pressed(SDL_SCANCODE_ESCAPE)) {
            return;
        }

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        this->update(std::min(ELAPSED_TIME, MAX_FRAME_TIME));
    }
}

void Game::update (double elapsed_time) {

}

void Game::draw (Graphics& graphics) {

}