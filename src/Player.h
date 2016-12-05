#pragma once

#include "constants.h"

class Player {

    int _x;
    int _y;
    
public:
    // Getters
    int xPos() const { return _x; }
    int yPos() const { return _y; }
    
    Player();
    ~Player();
    
    void move(int x, int y);
    void move(Vector2D direction);
    Vector2D getPos();
};