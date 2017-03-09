#pragma once

#include "Vector2D.h"

struct Body {
    Point location = {0, 0};
    Vector2D size = {0, 0};
    Vector2D velocity = {0, 0};
    Vector2D acceleration = {0, 0};

    // Should be able to do all of this with just velocity and gravity
    // but prototype it with explicit logic
    // bool isFalling;
    bool isJumping;

    int fallVelocity;
    int jumpVelocity;

    bool isMoving()
    {
        return velocity.x != 0 || acceleration.x != 0;
    };
};

inline std::ostream& operator<<(std::ostream& os, const Body& body)
{
    os << "loc [" << body.location.x << ", " << body.location.y << "]  ";
    return os;

}
