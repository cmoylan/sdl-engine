#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "Asset.h"


struct Sprite {
    Asset asset;
    SDL_Texture *texture;
};

typedef std::map<std::string, Sprite> SpriteMap;