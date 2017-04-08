#pragma once

#include <map>

#include "Vector2D.h"

using namespace std;

struct Body {
    Point mapLocation = {0, 0};
    Vector2D size = {0, 0};
    Vector2D velocity = {0, 0};
    Vector2D acceleration = {0, 0};

    // Should be able to do all of this with just velocity and gravity
    // but prototype it with explicit logic
    // bool isFalling;
    bool isJumping;

    int worldId = 0;

    // ----------
    //
    //  x1--x2
    //  |   |
    //  y1--y2
    //
    // because top left corner is closest to origin
    int upperLeft;
    int upperRight;
    int lowerLeft;
    int lowerRight;

    // FIXME: this is positive, it should not be
    int fallVelocity;
    int jumpVelocity;

    int x()
    {
        return mapLocation.x;
    };

    int y()
    {
        return mapLocation.y;
    };

    int width()
    {
        return size.x;
    };

    int height()
    {
        return size.y;
    };

    bool isMoving()
    {
        return velocity.x != 0 || acceleration.x != 0;
    };

    void calculateCollisionBox()
    {
        upperLeft = mapLocation.x;
        upperRight = mapLocation.x + size.x;
        lowerLeft = mapLocation.y;
        lowerRight = mapLocation.y + size.y;
    };
};

typedef map<int, Body> BodyMap;

inline std::ostream& operator<<(std::ostream& os, const Body& body)
{
    os << "loc [" << body.mapLocation.x << ", " << body.mapLocation.y << "]  ";
    return os;
}
