#include "TilesetManager.h"

void TilesetManager::add(const string name, Tileset tileset)
{
    tilesets[name] = tileset;
}


TilesetMap& TilesetManager::all()
{
    return tilesets;
}


Point TilesetManager::coordinatesFor(int gid)
{
    auto& tileset = findByGid(gid);
    return tileset.coordinatesFor(gid);
}


// FIXME: should raise exception if not found
// TODO: cache this in some kind of structure
Tileset& TilesetManager::findByGid(int gid)
{
    //cout << "looking for: " << gid << endl;
    for (auto& tilesetPair : tilesets) {
        auto& tileset = tilesetPair.second;
        //cout << "ts: " << tileset << endl;

        if ((tileset.firstGid <= gid) &&
                (tileset.lastGid >= gid)
           ) {
            return tileset;
        }
    }
    cout << "fuck: " << gid << endl;
    throw - 1;
}


Tileset& TilesetManager::get(const string name)
{
    return tilesets.at(name);
}

