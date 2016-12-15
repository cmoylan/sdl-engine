#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl_helpers.h"
#include "cleanup.h"

#include "Game.h"
#include "Sprite.h"


class Renderer {

    Game game;
    SpriteMap sprites;

    SDL_Renderer *renderer;
    SDL_Window *window;

public:
    Renderer();
    ~Renderer();

    void init(Game game);
    void run();
    void teardown();
    
    // Renderable methods
    /* copy the asset into an asset list
     * 
     */
    bool registerAsset(Asset& asset);

private:
    void initSDL();
};