#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <iostream>
#include <vector>

#define WINDOW_SCALE_FACTOR 70

struct Particle {int x, y, x_vel, y_vel;};

class Game {
public:
    Game();
    Game(Game &&) = default;
    Game(const Game &) = default;
    Game &operator=(Game &&) = default;
    Game &operator=(const Game &) = default;
    void RunTitleScreen();
    void Cleanup(int stage);
    ~Game();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_window_width = 16 * WINDOW_SCALE_FACTOR;
    int m_window_height = 9 * WINDOW_SCALE_FACTOR;
    SDL_Texture* m_bg_image;

    int m_particle_size = 2;
    std::vector<Particle> m_particles;
};
