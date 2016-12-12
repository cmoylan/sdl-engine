#pragma once

#include <iostream>

#include "constants.h"
#include "Drawable.h"
#include "Asset.h"


class Player : public Drawable {

    //int _x;
    //int _y;
    
    Asset *asset;

public:
    // Getters
    //int xPos() const { return _x; }
    //int yPos() const { return _y; }

    Player();
    ~Player();

    void move(int x, int y);
    void move(Vector2D direction);
    //virtual Vector2D getPos();
    
    AssetList getAssets();

};