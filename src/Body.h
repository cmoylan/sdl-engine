#pragma once

struct Body {
    Point location;
    Vector2D size;
    Vector2D velocity;

    // Should be able to do all of this with just velocity and gravity
    // but prototype it with explicit logic
    // bool isFalling;
    bool isJumping;

    int fallVelocity;
    int jumpVelocity;
};

inline std::ostream& operator<<(std::ostream& os, const Body& body)
{
    os << "loc [" << body.location.x << ", " << body.location.y << "]  ";
    return os;

}
