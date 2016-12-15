#pragma once

#include <iostream>
#include <vector>

#include "constants.h"
#include "Asset.h"


class Drawable {
    
    Asset *asset;
    
public:
    int _x = 0;
    int _y = 0;
    
    int x() { return _x; }
    int y() { return _y; }
    //Vector2D getPos();

};

typedef std::vector<Drawable> DrawList;