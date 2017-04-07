#pragma once

#include <map>

#include "Drawable.h"
#include "Vector2D.h"

using namespace std;

class LevelObject : public Drawable {
public:
//     LevelObject() {};
//     ~LevelObject() {};

    Vector2D position;
    Vector2D size;
    int gid;
    string name;
    // enum type
    bool visible;
    int _world_id;

    virtual AssetList assetData();
};

typedef map<string, LevelObject> LevelObjectMap;

// TODO: override operator<<

