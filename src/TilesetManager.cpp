#include "TilesetManager.h"

void TilesetManager::add(const string name, Tileset tileset)
{
    tilesets[name] = tileset;
}


TilesetMap& TilesetManager::all()
{
    return tilesets;
}


// FIXME: exception if gid not found???
string TilesetManager::assetNameFor(int gid)
{
    auto cached = _assetByGidCache.find(gid);
    if (cached != _assetByGidCache.cend()) {
        return cached->second;
    }

    for (const auto& tilesetPair : tilesets) {
        // first is tileset name
        // second is tileset
        const auto& tileset = tilesetPair.second;
        if (tileset.firstGid <= gid && tileset.lastGid >= gid) {
            //cout << "gid, fgid, lgid: " << gid << ", " << tileset.firstGid
            //     << ", " << tileset.lastGid << endl;
            //_assetByGidCache[gid] = tileset.filename;
            //_assetByGidCache.insert(pair<int, string>(gid, tileset.filename));
            return tileset.filename;
        }
    }
    // default to first thing
    return tilesets.begin()->second.filename;
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
    cout << "got a gid that wasn't in any tileset!: " << gid << endl;
    throw - 1;
}


Tileset& TilesetManager::get(const string name)
{
    return tilesets.at(name);
}

