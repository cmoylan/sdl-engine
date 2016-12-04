#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "res_path.h"
#include "sdl_helpers.h"
#include "cleanup.h"
#include "constants.h"
#include "Player.h"


class Game {
    
    Player *player;
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *image;
    
public:
    Game();
    
    ~Game();
    
    void teardown();
    void init();
    void render();
    void run();
};