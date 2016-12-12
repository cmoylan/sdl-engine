# pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Drawable.h"


struct Asset {
    std::string spriteFilename;
    SDL_Texture *sprite;
    int width;
    int height;
    int x;
    int y;
    /*int x() {
        (
    }*/;
    Drawable *parent;
};

typedef std::vector<Asset*> AssetList;