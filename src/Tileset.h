#pragma once

#include <map>
#include <string>
#include "Vector2D.h"

using namespace std;

// TODO:operator<< for Tileset
// we will need a way to find the correct tileset by GID
struct Tileset {
    // assume filename is relative to level respath
    string filename;
    int firstGid;
    int lastGid;
    int width;
    int height;
    int tileCount;
    int tileWidth;
    int tileHeight;
    int numRows;
    int numCols;

    void setCalculatedFields()
    {
        lastGid = firstGid + (tileCount - 1);
        numRows = height / tileHeight;
        numCols = width / tileWidth;
    };

    // TODO: cache this
    Vector2D coordinatesFor(int gid)
    {
        Vector2D coordinates;
        coordinates.x = (gid / numCols) * tileWidth;
        coordinates.y = (gid / numRows) * tileHeight;
        return coordinates;
    };
};

typedef map<string, Tileset> TilesetMap;

inline std::ostream& operator<<(std::ostream& os, const Tileset& ts)
{
    os << "tileset: [" << ts.filename;
    os << ", gids: " << ts.firstGid << "-" << ts.lastGid;
    os << "]";
    return os;
}