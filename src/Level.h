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
#include "Rectangle.h"
#include "Body.h"


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

// temp
// TODO: move to namespace
void printRenderData(RenderMap data);

class Level : private Drawable {

public:

    std::string levelFileName;
    // data about the overall map from level.json
    int mapWidth;
    int mapHeight;
    int textureTileWidth;
    int textureTileHeight;
    int playerStartX;
    int playerStartY;

    // other data - mostly for rendering
    LayerMap layers;
    TilesetMap tilesets;


    std::string resPath;  // FIXME: what sets this?

    // data about rendering
    int offsetX; // camera offset
    int offsetY; // TODO: could be a vector2d
    int tilePrefetch = 1; // can come from a config somewhere

    // ---- Members -------------------------------------------------- //
    Level();
    ~Level() {};

    // TODO: make a class method that can construct a level object
    bool loadFromJson(const std::string& filename);
    static Level constructFromJson(const std::string& filename);

    // NOTE: this blows up if run before `loadFromJson`
    void printPlatforms();

    /**
     * Return if an area on the map is blocked
     * @param x the origin x coord (lower left corner)
     * @param y the origin y coord
     * @param w the width of the rectangle
     * @param h the height of the rectangle
     */
    bool isBlocked(int originX, int originY, int sizeW, int sizeH);
    bool isOpen(int originX, int originY, int sizeW, int sizeH);

    /**
     * Return a vector to the closest location that is not blocked
     */
    Vector2D isOpenOrClosest(int originX, int originY,
                             int sizeW, int sizeH,
                             int velocityX, int velocityY);


    /**
       * Scroll by a pixel amount
       * @param pixelsX the amount to move left-right
       * @param pixelsY the amount to move up-down
       * @returns a boolean indicating if the level scrolled
       */
    bool scrollBy(int pixelsX, int pixelsY);
    bool scrollByX(int pixelsX);
    bool scrollByY(int pixelsY);

    /**
     * Get the indices of the tiles currently on screen
     * @return a list of indices whose tiles should be rendered
     */
    std::list<int> layerIndicesOnScreen();
    //std::list<int> tilesOnScreen();

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

    /**
     * Provide the offsets for rendering
     * @return an integer indicating how much the rendered level should be offset on screen
     */
    int screenOffsetX();
    int screenOffsetY();

    // these are kind of just "rendering indices x and y...
    /**
     * Determine how many tiles are on screen based on screen width
     */
    int tilesOnScreenX();

    /**
     * Determine how many tiles are on screen based on screen height
     */
    int tilesOnScreenY();

    /**
     * Return the sprite gid at a given point on screen
     */
    int valueAt(int x, int y, std::string layer = "platforms");

private:

    bool loadLayer(const std::string& layerName, const rapidjson::Value& data);
    bool loadMetadata(const rapidjson::Value& data);
    bool loadTileset(const rapidjson::Value& data);

    /**
     * Determine if a tile index is the end of the level row
     */
    bool isEndOfRow(size_t index, int sectorWidth = 0);

    // When the resolution is updated, _tilesOnScreenX/Y should be cleared
    int _tilesOnScreenX = 0;
    int _tilesOnScreenY = 0;

};
