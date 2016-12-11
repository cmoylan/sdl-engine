#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl_helpers.h"
#include "cleanup.h"

#include "Game.h"


class Renderer {

    Game game;

    SDL_Renderer *renderer;
    SDL_Window *window;
    // TODO: there will be lots of these textures
    SDL_Texture *image;

public:
    Renderer();
    ~Renderer();

    void init(Game game);
    void run();
    void teardown();

private:
    void initSDL();
};