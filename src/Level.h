#pragma once

#include <forward_list>
#include <list>
#include <map>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "file_helpers.h"
#include "res_path.h"
#include "sdl_helpers.h"
#include "utilities.h"

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
    void setCalculatedFields()
    {
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
    int gid;
};
typedef std::forward_list<Rectangle> RectangleList;
// string is the asset name, rect list is where to draw them
typedef std::map<std::string, RectangleList> RenderMap;


class Level : private Drawable {

    int mapWidth;
    int mapHeight;
    int textureTileWidth;
    int textureTileHeight;
    


    std::string levelFileName;

    LayerMap layers;
    TilesetMap tilesets;

public:

    std::string resPath;  // FIXME: what sets this?

    // TODO: could be a vector2d
    int offsetX;
    int offsetY;
    int tilesOnScreenX;
    int tilesOnScreenY;
    // take length of screen, divide by tilesOnScreenX
    int pixelsPerTileX;
    // take height of screen, divide by tilesOnScreenY
    int pixelsPerTileY;
    
    Level();
    ~Level() {};

    // TODO: make a class method that can construct a level object
    bool loadFromJson(const std::string& filename);

    // FIXME: this blows up if run before `loadFromJson`
    void printPlatforms();
    
    /**
     * Scroll by a pixel amount
     * @param pixelsX the amount to move left-right
     * @param pixelsY the amount to move up-down
     */
    void scrollBy(int pixelsX, int pixelsY);
    
    /**
     * Get the indices of the tiles currently on screen
     * @return a list of indices whose tiles should be rendered
     */
    std::list<int> tilesOnScreen();

    virtual AssetList assetData();

    /**
     * Return a bunch of render data
     * needs to return:
     * - x, y coords
     * - x, y clips
     * - for each tile on the screen
     *  [sprite1 => [
     *  { rect 1 }, { rect 2 }],
     *   sprite2 => [ ...etc... ]] 
     * @return a RenderMap with an entry for each layer
     */
    RenderMap renderData();

private:

    bool loadLayer(const std::string& layerName, const rapidjson::Value& data);
    bool loadTileset(const rapidjson::Value& data);

    /**
     * Determine if a tile index is the end of the level row
     */
    bool isEndOfRow(size_t index);
};
