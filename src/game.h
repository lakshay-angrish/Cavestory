#ifndef GAME_H
#define GAME_H

class Graphics;

class Game {
    private:
        void game_loop();
        void update (double elapsed_time);
        void draw (Graphics& graphics);
    public:
        Game();
        ~Game();
};

#endif