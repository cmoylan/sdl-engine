# pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


struct Asset {
    std::string spriteFilename;
    SDL_Texture *sprite;
    int width;
    int height;
};

typedef std::vector<Asset*> AssetList;