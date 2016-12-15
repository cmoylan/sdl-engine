#pragma once

#include <iostream>

#include "constants.h"
#include "Drawable.h"


class Player : public Drawable {  

public:

    Player();
    ~Player();

    void move(int x, int y);
    void move(Vector2D direction);

    AssetList assetData();
};