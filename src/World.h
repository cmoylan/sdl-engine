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

    Vector2D gravity;
    int acceleration;

public:
    World()
    {
        gravity.x = 0;
        gravity.y = -10;
        acceleration = 1;
        nextKey = 0;
    };
    ~World() {};

    /**
     * Performs processing for the current game cycle
     */
    void tick();

    /**
     * Add a body to the world body vector and return a reference/int
     */
    size_t addBody(Body body);
    size_t addBody(int originX, int originY, int sizeW, int sizeH);

    void setMap(std::shared_ptr<Level> level);

    /**
     * Will return a reference to the body identified by `id`
     * @param id the id of the Body
     *
     * TODO: should throw an exception if the id is not found
     */
    Body& get(size_t id);
    Point getPosition(size_t id);

    /**
     * Determine if a given Body can fall
     */
    bool canFall(size_t id);
    bool canFall(const Body& body);

    /**
     * Try to move by a given velocity
     *
     * @return a Vector2D of the velocity the body moved
     */
    Vector2D tryMove(size_t id, Vector2D velocity);
    Vector2D tryMove(size_t id, int velocityX, int velocityY);
};
