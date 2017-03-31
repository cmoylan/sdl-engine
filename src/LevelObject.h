#pragma once

#include <map>

#include "Vector2D.h"

using namespace std;

struct LevelObject {
    Vector2D position;
    Vector2D size;
    int gid;
    string name;
    // enum type
    bool visible;
    int _world_id;
};

typedef map<string, LevelObject> LevelObjectMap;

// TODO: override operator<<
