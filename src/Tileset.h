#pragma once

#include <iostream>
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
    int width; // this is tile width/height
    int height;
    int tileCount;
    int tileWidth;
    int tileHeight;
    int numRows;
    int numCols;
    int imageWidth;
    int imageHeight;

    void setCalculatedFields()
    {

        lastGid = firstGid + (tileCount - 1);
        numRows = height / tileHeight;
        numCols = width / tileWidth;
    };

    // TODO: cache this
    // FIXME: test this
    Vector2D coordinatesFor(int gid)
    {
        int normalizedGid = gid - firstGid;
        Vector2D coordinates;
        coordinates.x = (normalizedGid % numCols) * tileWidth;
        coordinates.y = (normalizedGid / numCols) * tileHeight;
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