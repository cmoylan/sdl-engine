#pragma once

#include <forward_list>
#include <map>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "file_helpers.h"
#include "res_path.h"
#include "sdl_helpers.h"

#include "Asset.h"
#include "Drawable.h"


struct Layer {
    int tileCount;
    std::vector<int> tiles;
    int width;
    int height;
};
typedef std::map<std::string, Layer> LayerMap;


struct Tileset {
    // assume filename is relative to level respath
    std::string filename;
    int firstGid;
    int lastGid;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    int numRows;
    int numCols;
    //float scaleFactorX;
    //float scaleFactorY;
    void setCalculatedFields() {
        lastGid = firstGid + (
            (width / tileWidth) * (height / tileHeight)) - 1;
        numRows = height / tileHeight;
        numCols = width / tileWidth;
    };
};
typedef std::map<std::string, Tileset> TilesetMap;


// FIXME: this name is not descriptive
// it's the information to render one rectangle on screen
struct Rectangle {
    int x;
    int y;
    int clipX;
    int clipY;
};
typedef std::forward_list<Rectangle> RectangleList;
// string is the asset name, rect list is where to draw them
typedef std::map<std::string, RectangleList> RenderMap;


class Level :private Drawable {

    int mapWidth;
    int mapHeight;
    int tileWidth;
    int tileHeight;

    std::string levelFileName;
    
    LayerMap layers; 
    TilesetMap tilesets;
    
public:
    
    std::string resPath;  // FIXME: what sets this?

    Level() {};
    ~Level() {};

    // TODO: make a class method that can construct a level object
    bool loadFromJson(const std::string& filename);

    void printPlatforms();

    virtual AssetList assetData();
    
    /**
     * Return a bunch of render data
     * needs to return:
     * - x, y coords
     * - x, y clips
     * - for each tile on the screen
     */
    RenderMap renderData();
    
private:

    bool loadLayer(const std::string& layerName, const rapidjson::Value& data);
    bool loadTileset(const rapidjson::Value& data);

};