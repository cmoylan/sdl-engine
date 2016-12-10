#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "res_path.h"
#include "sdl_helpers.h"
#include "cleanup.h"

#include "constants.h"
#include "Level.h"
#include "Player.h"


struct Options {
    int levelNumber;
    int score;
    std::string levelPath;
};


class Game {

    Options options;
    Player player;
    Level level;
    
    SDL_Window *window;
    SDL_Texture *image;

public:
    SDL_Renderer *renderer;

    Game();
    ~Game();

    void load(Options options);
    void teardown();
    void init();
    void render();
    void run();
};