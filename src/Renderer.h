#pragma once

#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sdl_helpers.h"
#include "cleanup.h"

#include "FontManager.h"
#include "Game.h"
#include "Sprite.h"


class Renderer {

    Game game;
    SpriteMap sprites;

    FontManager fonts;

    SDL_Renderer *renderer;
    SDL_Window *window;

    //temp
    bool RENDER_DATA_PRINTED = true;

public:
    Renderer() {};
    ~Renderer() {};

    void init(Game game);
    void run();
    void teardown();

    // Renderable methods
    /* create a sprite based on the asset
     * and copy it into the spritemap
     */
    bool registerAsset(Asset& asset);


private:
    void initSDL();
    void drawTerminal();
    void drawLevel();
    void drawEntities();
    void drawPlayer();
    void displayDebugInfo();
};
