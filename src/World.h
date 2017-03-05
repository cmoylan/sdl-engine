#pragma once

#include <vector>
#include "constants.h"


struct Body {
    Point location;
    Vector2D size;
    Vector2D velocity;
};

class World {

    std::vector<Body> bodies;
    // int gravity;

public:
    World() {};
    ~World() {};

    /**
     * Will add a body to the world body vector and return a reference/int
     */
    size_t add(Body body);

    /**
     * Will return a reference to the body identified by `id`
     */
    Body& get(size_t id);

};