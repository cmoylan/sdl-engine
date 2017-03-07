#include "World.h"

size_t World::addBody(Body body)
{
    int key = nextKey;
    bodies.insert(pair<int, Body>(key, body));
    nextKey += 1;
    return key;
}


size_t World::addBody(int originX, int originY, int sizeW, int sizeH)
{
    Body body = {};

    Point location = {originX, originY};
    body.location = location;

    Vector2D size = {sizeW, sizeH};
    body.size = size;

    Vector2D velocity = {0, 0};
    body.velocity = velocity;

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


Point World::getPosition(size_t id)
{
    Body body = get(id);
    return body.location;
}


void World::setMap(shared_ptr<Level> level)
{
    map = level;
}


void World::tick()
{
    int fallVelocity = 10;
    // try to make every body fall
    Vector2D newVelocity = {0, 0};
    for (auto& bodyPair : bodies) {
        auto& body = bodyPair.second;

        if (canFall(body)) {
            //cout << "trying to fall: " << newVelocity << endl;
            newVelocity = map->isOpenOrClosest(body.location.x, body.location.y,
                                               body.size.x, body.size.y,
                                               0, fallVelocity);
            body.location.x += newVelocity.x;
            body.location.y += newVelocity.y;
            cout << "body: " << body; // << endl;
        }
    }
}


Vector2D World::tryMove(size_t id, Vector2D velocity)
{
    return tryMove(id, velocity.x, velocity.y);
}

Vector2D World::tryMove(size_t id, int velocityX, int velocityY)
{
    Body& body = get(id);
    Vector2D velocity = map->isOpenOrClosest(body.location.x, body.location.y,
                        body.size.x, body.size.y,
                        velocityX, velocityY);
    body.location.x += velocity.x;
    body.location.y += velocity.y;

    return velocity;
}
