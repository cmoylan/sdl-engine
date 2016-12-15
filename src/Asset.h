# pragma once

#include <map>
#include <string>
#include <vector>


struct Asset {
    std::string name;
    std::string spriteFilename;
    //SDL_Texture *sprite;
    int width;
    int height;
};

typedef std::vector<Asset> AssetList;

typedef std::map<std::string, Asset> AssetMap;