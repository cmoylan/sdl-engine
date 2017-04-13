#pragma once

#include <map>

#include "guile.h"

#include "Drawable.h"
#include "MessageCentre.h"
#include "Vector2D.h"

using namespace std;

// this is entity. if we need level objects we'll make them
class Entity : public Drawable {
public:
//     LevelObject() {};
//     ~LevelObject() {};

    //int gid = 0;
    string name;
    // enum type
    bool visible;
    int _world_id;

    virtual AssetList assetData();

    void handleCollisionEvent(Message message);
};

typedef map<string, Entity> EntityMap;

// TODO: override operator<<

