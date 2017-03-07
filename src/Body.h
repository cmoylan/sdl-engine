#pragma once

struct Body {
    Point location;
    Vector2D size;
    Vector2D velocity;

    bool isFalling;
};

inline std::ostream& operator<<(std::ostream& os, const Body& body)
{
    os << "loc [" << body.location.x << ", " << body.location.y << "]  ";
    return os;

}
