#include "World.h"

// external
size_t World::addBody(Body body)
{
    int key = nextKey;
    bodies.insert(pair<int, Body>(key, body));
    nextKey += 1;
    return key;
}


// external
size_t World::addBody(int originX, int originY, int sizeW, int sizeH)
{
    Body body = {};

    Point location = {originX, originY};
    body.location = location;

    Vector2D size = {sizeW, sizeH};
    body.size = size;

    Vector2D velocity = {0, 0};
    body.velocity = velocity;

    body.isJumping = false;

    return addBody(body);
}


bool World::canFall(size_t id)
{
    Body& body = get(id);
    return canFall(body);
}


bool World::canFall(const Body& body)
{
    return map->isOpen(body.location.x, body.location.y + 1,
                       body.size.x, body.size.y);
}


Body& World::get(size_t id)
{
    return bodies.at(id);
}


// external
Point World::getPosition(size_t id)
{
    Body body = get(id);
    return body.location;
}


// external
void World::setMap(shared_ptr<Level> level)
{
    map = level;
}


// external
void World::tick()
{
    // try to make every body fall
    for (auto& bodyPair : bodies) {
        auto& body = bodyPair.second;

        if (body.isMoving()) {
            handleMove(body);
        }

        if (body.isJumping) {
            handleJump(body);
        }
        else {
            handleFall(body);
        }
    }
}


void World::handleFall(Body& body)
{
    if (canFall(body)) {
        // cout << "trying to fall" << endl;
        if (body.fallVelocity < fallTerminalVelocity) {
            body.fallVelocity += fallAcceleration;
        }
        Vector2D newVelocity = map->isOpenOrClosest(body.location.x, body.location.y,
                               body.size.x, body.size.y,
                               0, body.fallVelocity);
        body.location.x += newVelocity.x;
        body.location.y += newVelocity.y;
    }
}


void World::handleJump(Body& body)
{
    if (body.jumpVelocity > 0) {
        body.jumpVelocity -= jumpDecay;
        Vector2D newVelocity = map->isOpenOrClosest(body.location.x, body.location.y,
                               body.size.x, body.size.y,
                               0, body.jumpVelocity);
        body.location.y -= body.jumpVelocity;
    }
    if (body.jumpVelocity == 0) {
        body.isJumping = false;
        body.fallVelocity = 0;
    }
}


// FIXME: some weird quirks in here
// smooth out keyboard input first
void World::handleMove(Body& body)
{
    // TODO: separate function?
    int newVelocityX = body.velocity.x;
    if (body.acceleration.x != 0) {
        // FIXME: magic number!
        newVelocityX = Utilities::sumFromOrigin(newVelocityX, 2);
        body.acceleration.x = Utilities::differenceToOrigin(body.acceleration.x, 1);
    }



    Vector2D velocity = map->isOpenOrClosest(body.location.x, body.location.y,
                        body.size.x, body.size.y,
                        newVelocityX, 0);

    body.velocity.x = velocity.x;
    body.location.x += body.velocity.x;

    body.velocity.x = Utilities::differenceToOrigin(body.velocity.x, friction);
}


// external
void World::tryJump(size_t id)
{
    Body& body = get(id);
    body.isJumping = true;
    body.jumpVelocity = 10; // FIXME: magic number
    //Vector2D velocity = {0,0};
    //return velocity;
}


// external
void World::tryMove(size_t id, Vector2D velocity)
{
    tryMove(id, velocity.x, velocity.y);
}


void World::tryMove(size_t id, int velocityX, int velocityY)
{
    // FIXME: magic numbers
    Body& body = get(id);
//     body.acceleration.x = 2;
//
//     if (body.velocity.x == 0) {
//         body.velocity.x = (velocityX >= 0) ? 1 : -1;
//     }


    Vector2D velocity = map->isOpenOrClosest(body.location.x, body.location.y,
                        body.size.x, body.size.y,
                        velocityX, velocityY);
    body.location.x += velocity.x;
    body.location.y += velocity.y;

    //return velocity;
}
