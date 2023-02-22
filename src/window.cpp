#pragma once
#include "window.hpp"

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error at SDL_Init. " << SDL_GetError() << std::endl;
        exit(1);
    }

    int flags = IMG_INIT_PNG; 
    if((IMG_Init(flags) & flags) != flags) {
        std::cout << "Error at IMG_Init. " << SDL_GetError() << std::endl;
        Cleanup(1);
        exit(1);
    }

    if (TTF_Init() != 0) {
        std::cout << "Error at TTF_Init. " << SDL_GetError() << std::endl;
        Cleanup(2);
        exit(1);
    }

    m_window = SDL_CreateWindow("Balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        Cleanup(3);
        std::cout << "Error at SDL_CreateWindow. " << SDL_GetError() << std::endl;
        exit(1);
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        std::cout << "Error at SDL_CreateRenderer. " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        Cleanup(3);
        exit(1);
    }

    m_bg_image = IMG_LoadTexture(m_renderer, "res/images/one.jpg");
    if (m_bg_image == nullptr) {
        std::cout << "Error at IMG_LoadTexture. " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_DestroyRenderer(m_renderer);
        Cleanup(3);
        exit(1);
    }

    // Generating particles
    for (int i = 0; i < 100; i++) {
        m_particles.push_back(Particle { 
                .x = rand() % m_window_width,
                .y = rand() % m_window_height,
                .x_vel = rand() % 10,
                .y_vel = rand() % 10,
            }
        );
    }
}

void Game::RunTitleScreen() {
    TTF_Font* font = TTF_OpenFont("res/fonts/OpenSans-Semibold.ttf" , 35);
    SDL_Surface* font_surface = TTF_RenderText_Solid(font, "Balls", SDL_Color {255, 255, 255});
    SDL_Texture* font_texture = SDL_CreateTextureFromSurface(m_renderer, font_surface);
    SDL_Rect font_src;
    SDL_QueryTexture(font_texture, NULL, NULL, &font_src.w, &font_src.h);
    SDL_Rect font_dst {
        (m_window_width / 2) - font_src.w / 2,
        100, 
        font_src.w, 
        font_src.h
    };

    bool running {true};
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        SDL_RenderClear(m_renderer);

        SDL_RenderCopy(m_renderer, m_bg_image, NULL, NULL);

        SDL_RenderCopy(m_renderer, font_texture, NULL, &font_dst);

        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);

        for (auto p : m_particles) {
            SDL_Rect temp_p {.x = p.x, .y = p.y, .w = m_particle_size, .h = m_particle_size};
            SDL_RenderDrawRect(m_renderer, &temp_p);
        }

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);

        SDL_RenderPresent(m_renderer);

        for (auto &p : m_particles) {
            p.x += p.x_vel;
            p.y += p.y_vel;

            if (p.x > m_window_width || p.y > m_window_height) {
                p.x = rand() % m_window_width;
                p.y = rand() % m_window_height;
            }
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyTexture(font_texture);
}

void Game::Cleanup(int stage) {
    switch (stage) {
        case 1: 
            SDL_Quit();
            break;

        case 2:
            IMG_Quit();
            SDL_Quit();
            break;

        case 3:
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            break;

        default:
            std::cout << "[Error] Wrong stage number.\n";
            break;
    }
}

Game::~Game() {
    SDL_DestroyTexture(m_bg_image);
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    Cleanup(3);
}

