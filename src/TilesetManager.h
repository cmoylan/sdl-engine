#pragma once

#include <iostream>
#include <map>
#include <string>
#include "Tileset.h"
#include "Vector2D.h"

using namespace std;

class TilesetManager {

    map<string, Tileset> tilesets;


public:
    TilesetManager() {};
    ~TilesetManager() {};

    Tileset& findByGid(int gid);
    TilesetMap& all();
    void add(const string name, Tileset tileset);
    Tileset& get(const string name);
    Point coordinatesFor(int gid);

};