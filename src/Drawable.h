#pragma once

#include <iostream>
#include <vector>

#include "constants.h"
#include "Asset.h"


class Drawable {
    
public:
    
    Asset asset;
    
    int _x = 0;
    int _y = 0;
    
    int x() { return _x; }
    int y() { return _y; }
    //Vector2D getPos();

    // should return x, y, renderable asset, clips [if any]
    // for objects that have multiple assets to draw [level]
    // this should return a list of assets and their associated
    // metadata
    // --- currently not used
    void renderData();
};

// TODO: rename
typedef std::vector<Drawable> DrawList;