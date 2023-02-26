#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <iostream>

void render_level_one(SDL_Renderer* renderer, bool &game_running) {

    bool level_running {true};
    SDL_Event event;

    SDL_Texture* level_bg_image {IMG_LoadTexture(renderer, "res/images/two.jpg")};
    if (level_bg_image == nullptr) {
        std::cout << "Failed to load level one img.\n";
    }

    while (level_running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    level_running = false;
                    game_running = false;
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_BACKSPACE:
                            level_running = false;
                            break;

                        default:
                            break;
                    }

                default:
                    break;
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, level_bg_image, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(level_bg_image);
}
