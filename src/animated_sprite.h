#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include "globals.h"
#include <map>
#include <string>
#include <vector>

class Graphics;

class AnimatedSprite: public Sprite {
    private:
        std::map<std::string, std::vector<SDL_Rect> > _animations;
        std::map<std::string, Vector2> _offsets;
        int _frame_index;
        double _elapsed_time;
        bool _visible;

    protected:
        std::string _current_animation;
        bool _current_animation_once;
        double _time_to_update;
        void add_animation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);
        void reset_animation();
        void stop_animation();
        void set_visible(bool visible);
        virtual void animation_done(std::string current_animation);

    public:
        AnimatedSprite();
        AnimatedSprite(Graphics& graphics, std::string path, int source_x, int source_y, int width, int height, double x_pos, double y_pos, double time_to_update);

        void play_animation(std::string animation, bool once = false);
        void update(int elapsed_time);
        void draw(Graphics& graphics, int x, int y);
        virtual void setup_animation();
};

#endif