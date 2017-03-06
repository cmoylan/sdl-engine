#pragma once

struct Body {
    Point location;
    Vector2D size;
    Vector2D velocity;
    bool isFalling;
};

// TODO: override operator<<