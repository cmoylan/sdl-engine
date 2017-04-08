#pragma once

#include <iostream>

#include "constants.h"
#include "Drawable.h"
#include "Vector2D.h"


class Player : public Drawable {

public:

    Player();
    ~Player();

    //void move(int x, int y);
    //void move(Vector2D direction);

    void setScreenPositionFromOffset(int x, int y);

    // Point spriteClips()

    AssetList assetData();
};
