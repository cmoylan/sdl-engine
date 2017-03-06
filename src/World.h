#pragma once

#include <memory>
#include <map>

#include "constants.h"
#include "Body.h"
#include "Level.h"



class World {

    std::map<int, Body> bodies;
    int nextKey;

    std::shared_ptr<Level> map;

    int gravity;
    int acceleration;

public:
    World()
    {
        gravity = 1;
        acceleration = 1;
        nextKey = 0;
    };
    ~World() {};

    /**
     * Will add a body to the world body vector and return a reference/int
     */
    size_t addBody(Body body);
    size_t addBody(int originX, int originY, int sizeW, int sizeH);

    /**
     * Will return a reference to the body identified by `id`
     */
    Body& get(size_t id);
    Point getPosition(size_t id);

    void setMap(std::shared_ptr<Level> level);

    void tick();

    Vector2D tryMove(size_t id, Vector2D velocity);
    Vector2D tryMove(size_t id, int velocityX, int velocityY);
};