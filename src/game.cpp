#include "game.h"
#include "graphics.h"
#include "input.h"
#include "slope.h"

#include <SDL2/SDL.h>

// The main game loop

namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 1000 / FPS;
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

    //level needs to be initialized first
    this->_level = Level("Map 1", graphics);
    this->_player = Player(graphics, this->_level.get_player_spawn_point());
    this->_hud = HUD(graphics, this->_player);

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

        } else if (input.is_key_held(SDL_SCANCODE_LEFT)) {
            this->_player.move_left();

        } else if (input.is_key_held(SDL_SCANCODE_RIGHT)) {
            this->_player.move_right();

        }

        if (input.is_key_held(SDL_SCANCODE_UP)) {
            this->_player.look_up();

        } else if (input.is_key_held(SDL_SCANCODE_DOWN)) {
            this->_player.look_down();
        }

        if (input.was_key_released(SDL_SCANCODE_UP) == true) {
			this->_player.stop_looking_up();
		}

        if (input.was_key_released(SDL_SCANCODE_DOWN) == true) {
			this->_player.stop_looking_down();
		}

        if (input.was_key_pressed(SDL_SCANCODE_Z) == true) {
			this->_player.jump();
		}

        if (!input.is_key_held(SDL_SCANCODE_LEFT) && !input.is_key_held(SDL_SCANCODE_RIGHT)) {
            this->_player.stop_moving();
        }

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        this->_graphics = graphics;
        this->update(std::min(ELAPSED_TIME, MAX_FRAME_TIME));

        this->draw(graphics);
    }
}

void Game::update (double elapsed_time) {
    this->_player.update(elapsed_time);
    this->_level.update(elapsed_time, this->_player);
    this->_hud.update(elapsed_time, this->_player);

    //check for collisions;
    std::vector<Rectangle> others = this->_level.check_tile_collisions(this->_player.get_bounding_box());
    if (others.size() > 0) {
        this->_player.handle_tile_collisions(others);
    }
    //slopes
    std::vector<Slope> other_slopes = this->_level.check_slope_collisions(this->_player.get_bounding_box());
    if (other_slopes.size() > 0) {
        this->_player.handle_slope_collisions(other_slopes);
    }
    //doors
    std::vector<Door> other_doors = this->_level.check_door_collisions(this->_player.get_bounding_box());
    if (other_doors.size() > 0) {
        this->_player.handle_door_collision(other_doors, this->_level, this->_graphics);
    }
    //enemies
    std::vector<Enemy*> enemies = this->_level.check_enemy_collisions(this->_player.get_bounding_box());
    if (enemies.size() > 0) {
        this->_player.handle_enemy_collisions(enemies);
    }
}

void Game::draw (Graphics& graphics) {
    graphics.clear();
    this->_level.draw(graphics);
    this->_player.draw(graphics);
    this->_hud.draw(graphics);
    graphics.flip();
}