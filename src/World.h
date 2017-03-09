#pragma once

#include <memory>
#include <map>

#include "constants.h"
#include "Body.h"
#include "Level.h"
#include "Vector2D.h"


// TODO: need to clearly separate public and private methods so the interface
//       confusing as hell
class World {

    std::map<int, Body> bodies;
    int nextKey = 1;

    std::shared_ptr<Level> map;

    Vector2D gravity;
    int acceleration;
    int friction;

    int jumpTerminalVelocity;
    int jumpDecay; // how much does the jump deccelerate

    int fallAcceleration;
    int fallTerminalVelocity;

public:

    // TODO: allow all of this to be configured
    World()
    {
        gravity.x = 0;
        gravity.y = -10;

        jumpTerminalVelocity = 20;
        jumpDecay = 1;
        fallAcceleration = 1;
        fallTerminalVelocity = 10;

        friction = 1;
        //acceleration = 1; // not used
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
     * Try to jump
     */
    void tryJump(size_t id);

    /**
     * Try to move by a given velocity
     *
     * @return a Vector2D of the velocity the body moved
     */
    void tryMove(size_t id, Vector2D velocity);
    void tryMove(size_t id, int velocityX, int velocityY);

private:

    /**
     * Determine if a given Body can fall
     */
    bool canFall(size_t id);
    bool canFall(const Body& body);

    /**
     * Attempt to handle a jump, if the body is jumping
     */
    void handleJump(Body& body);

    /**
     * Attempt to handle a fall if the body is falling
     */
    void handleFall(Body& body);

    /**
     * Attempt to handle a move if the body is moving
     */
    void handleMove(Body& body);
};
