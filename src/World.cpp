#include "World.h"

// external
size_t World::addBody(Body body)
{
    int worldId = nextWorldId;
    body.worldId = worldId;
    bodies.insert(pair<int, Body>(worldId, body));
    nextWorldId += 1;
    return worldId;
}


// external
size_t World::addBody(int originX, int originY, int sizeW, int sizeH)
{
    Body body = {};

    Point location = {originX, originY};
    body.mapLocation = location;

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
    return map->isOpen(body.mapLocation.x, body.mapLocation.y + 1,
                       body.size.x, body.size.y);
}


void World::checkCollisions()
{
//cout << " ---- collision run --- " <<endl;
//     for (auto it = mymap.cbegin(); it != mymap.cend(); ++it)
//     std::cout << " [" << (*it).first << ':' << (*it).second << ']';
//
    // runs once per clock cycle
    for (auto bodyPair : bodies) {
        // bodyPair.first; // is the body id
        Body& firstBody = bodyPair.second;

        // for it's seemingly convaluded logic, this works
        // a->b, a->c, a->d
        // b->c, b->d
        // c->d
        BodyMap::iterator comparator = bodies.find(bodyPair.first);
        comparator++;
        if (comparator == bodies.end()) { return; }

        for (; comparator != bodies.end(); ++comparator) {
            //cout << "comparing x to x: " << body.worldId << " | " << comparator->second.worldId << endl;
            Body& secondBody = comparator->second;
            CollisionPair cacheLookup(firstBody.worldId, secondBody.worldId);

            if (isCollision(firstBody, secondBody)) {
                // if not in collisions
                if (currentCollisions.find(cacheLookup) == currentCollisions.end()) {
                    currentCollisions.insert(cacheLookup);
                    // notify listeners
                    Message message = {firstBody.worldId};
                    messageCentre().publish("collision", message);
                    cout << "first body: " << firstBody.worldId;
                    cout << " | second: " << secondBody.worldId << endl;
                }

            } else {
                // remove it from collisions if it's there
                auto cache = currentCollisions.find(cacheLookup);
                if (cache != currentCollisions.end()) {
                    //cout << "found a collision which we are removing" << endl;
                    currentCollisions.erase(cache);
                    // TODO: broadcast a message here
                }
            }
        }

    }

//     for (auto it = bodies.cbegin(); it != bodies.cend();) {
//         auto first = it;
//         auto second = ++it;
//
//         *it.second; // first element
//
//     }
}


Body& World::get(size_t id)
{
    return bodies.at(id);
}


// external
Point World::getPosition(size_t id)
{
    Body body = get(id);
    return body.mapLocation;
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

    checkCollisions();
}


void World::handleFall(Body& body)
{
    if (canFall(body)) {
        // cout << "trying to fall" << endl;
        if (body.fallVelocity < fallTerminalVelocity) {
            body.fallVelocity += fallAcceleration;
        }
        Vector2D newVelocity = map->isOpenOrClosest(body.mapLocation.x,
                               body.mapLocation.y,
                               body.size.x, body.size.y,
                               0, body.fallVelocity);
        body.mapLocation.x += newVelocity.x;
        body.mapLocation.y += newVelocity.y;
    }
}


// FIXME: don't do this negation stuff, fix jumpVelocity
void World::handleJump(Body& body)
{
    if (body.jumpVelocity > 0) {
        body.jumpVelocity -= jumpDecay;
        //cout << "jump velocity " << body.jumpVelocity << endl;
        Vector2D newVelocity = map->isOpenOrClosest(body.mapLocation.x,
                               body.mapLocation.y - 4,
                               body.size.x, body.size.y,
                               0, -body.jumpVelocity);

        body.jumpVelocity = -newVelocity.y;
        body.mapLocation.y -= body.jumpVelocity;

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



    Vector2D velocity = map->isOpenOrClosest(body.mapLocation.x, body.mapLocation.y,
                        body.size.x, body.size.y,
                        newVelocityX, 0);

    body.velocity.x = velocity.x;
    body.mapLocation.x += body.velocity.x;

    body.velocity.x = Utilities::differenceToOrigin(body.velocity.x, friction);
}


bool World::isCollision(Body& rect1, Body& rect2)
{
    //a.calculateCollisionBox();
    //b.calculateCollisionBox();

//     left1 = object1->x + object1->col_x_offset;
//     left2 = object2->x + object2->col_x_offset;
//     right1 = left1 + object1->col_width;
//     right2 = left2 + object2->col_width;
//     top1 = object1->y + object1->col_y_offset;
//     top2 = object2->y + object1->col_y_offset;
//     bottom1 = top1 + object1->col_height;
//     bottom2 = top2 + object2->col_height;
//
//     if (bottom1 < top2) return(0);
//     if (top1 > bottom2) return(0);
//
//     if (right1 < left2) return(0);
//     if (left1 > right2) return(0);

//     if (
//         ((a.upperLeft < b.upperRight) || (a.upperRight > b.upperLeft))
//         &&
//         ((a.lowerLeft < b.lowerRight) || (a.lowerRight > b.lowerLeft))
//     ) {
//         return true;
//     }

    if (rect1.x() < rect2.x() + rect2.width() &&
            rect1.x() + rect1.width() > rect2.x() &&
            rect1.y() < rect2.y() + rect2.height() &&
            rect1.height() + rect1.y() > rect2.y()) {
        // collision detected!
        return true;
    }

    return false;
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


// FIXME: rewrite this
void World::tryMove(size_t id, int velocityX, int velocityY)
{
    // FIXME: magic numbers
    Body& body = get(id);
//     body.acceleration.x = 2;
//
//     if (body.velocity.x == 0) {
//         body.velocity.x = (velocityX >= 0) ? 1 : -1;
//     }


    Vector2D velocity = map->isOpenOrClosest(body.mapLocation.x, body.mapLocation.y,
                        body.size.x, body.size.y,
                        velocityX, velocityY);
    body.mapLocation.x += velocity.x;
    body.mapLocation.y += velocity.y;

    //return velocity;
}
