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

    //
    //
    // should have level and screen positions
    //
    //
    int _levelX = 0 ;
    int _levelY = 0;
    int _screenX = 0;
    int _screenY = 0;
    int _w = 0;
    int _h = 0;
    int gid = 0;

    bool centerOn = false;
    //
    // May need to keep track of screen and level position
    // now that this includes level objects, they can be off screen
    // unlike the player which is always on screen
    //

    std::string assetName;

    int _x = 0;
    int _y = 0;
    // this
    int spriteOffsetX = 32;
    int spriteOffsetY = 32;

    // Copy constructor
    // Drawable(const Drawable& d);// {
//     num = a.num;   // Number of elements in "array"
//     array = new int[num];
//     for (int i = 0; i < num; i++) {
//         array[i] = a.array[i];
//     }
    //}

    int levelX() { return _levelX; }
    int levelY() { return _levelY; }
    int screenX() { return _screenX; }
    int screenY() { return _screenY; }
    int w() { return _w;}
    int h() { return _h; }

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
    virtual AssetList assetData() =0; // *NOPAD*

    void levelMove(int x, int y)
    {
        // and then always update level pox
        this->_levelX += x;
        this->_levelY += y;
    };

    void levelSetPosition(int x, int y)
    {
        _levelX = x;
        _levelY = y;
    };

    bool levelPositionEquals(int x, int y)
    {
        return _levelX == x && _levelY == y;
    }

    void screenMove(int x, int y)
    {

        // and on the screen
        this->_screenX += x;
        this->_screenY += y;
    }

    void screenSetPosition(int x, int y)
    {
        _screenX = x;
        _screenY = y;
    }

    void setScreenPositionFromOffset(int offsetX, int offsetY)
    {
        _screenX = _levelX - offsetX;
        _screenY = _levelY - offsetY;
    };

    void setSize(int w, int h)
    {
        _w = w;
        _h = h;
    }
};

// TODO: use the safe pointer
//typedef std::vector<std::unique_ptr<Drawable>> DrawList;
typedef std::vector<Drawable*> DrawableList;
