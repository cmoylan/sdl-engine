#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl_helpers.h"
#include "cleanup.h"

#include "Asset.h"
#include "Game.h"


class Renderer {

    Game game;

    SDL_Renderer *renderer;
    SDL_Window *window;
    
    std::vector<Asset> assets;

public:
    Renderer();
    ~Renderer();

    void init(Game game);
    void run();
    void teardown();
    
    // Renderable methods
    bool registerAsset(Asset options);

private:
    void initSDL();
};