#pragma once

#include <map>

#include "Vector2D.h"

using namespace std;

struct Body {
    Point location = {0, 0};
    Vector2D size = {0, 0};
    Vector2D velocity = {0, 0};
    Vector2D acceleration = {0, 0};

    // Should be able to do all of this with just velocity and gravity
    // but prototype it with explicit logic
    // bool isFalling;
    bool isJumping;
    
    // ----------
    //
    //  x1--x2
    //  |   |
    //  y1--y2
    //
    // because top left corner is closest to origin
    int x1;
    int x2;
    int y1;
    int y2;

    // FIXME: this is positive, it should not be
    int fallVelocity;
    int jumpVelocity;

    bool isMoving()
    {
        return velocity.x != 0 || acceleration.x != 0;
    };
    
    void calculateCollisionBox() 
    {
        x1 = location.x;
        x2 = location.x + size.x;
        y1 = location.y;
        y2 = location.y + size.y;
    };
};

typedef map<int, Body> BodyMap;

inline std::ostream& operator<<(std::ostream& os, const Body& body)
{
    os << "loc [" << body.location.x << ", " << body.location.y << "]  ";
    return os;
}
