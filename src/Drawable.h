#pragma once

#include <iostream>
//#include <memory>
#include <string>
#include <vector>

#include "constants.h"
#include "Asset.h"


// TODO: this should know which asset it needs
class Drawable {
    
public:

    std::string assetName;
    
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
    //void renderData();
    
    /* returns either enough data to create an asset,
     * or an asset without any SDL stuff
     * 
     */
    virtual AssetList assetData() =0;
};

// TODO: use the safe pointer
//typedef std::vector<std::unique_ptr<Drawable>> DrawList;
typedef std::vector<Drawable*> DrawList;
