#pragma once

#include <map>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include "Asset.h"

struct Sprite {
    Asset asset;
    SDL_Texture *sprite;
};

typedef std::map<std::string, Sprite> SpriteMap;