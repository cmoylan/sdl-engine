#include "World.h"

size_t World::add(Body body)
{
    bodies.push_back(body);
    return bodies.size();
}


Body& World::get(size_t id)
{
    return bodies.at(id);
}
