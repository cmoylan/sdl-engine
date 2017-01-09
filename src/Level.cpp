#include "Level.h"


Level::Level() 
{
    offsetX = 0;
    offsetY = 0;
    // TODO: comes from constants or something
    tilesOnScreenX = 20;
    tilesOnScreenY = 20;
}


AssetList Level::assetData()
{
    AssetList assets;
    // load assets from tilesets
    for (auto& tilesetPair : this->tilesets) {
        // load into an asset, append to asset list
        Tileset& tileset = tilesetPair.second;

        Asset asset = {};
        asset.spriteFilename = tileset.filename;
        asset.width = tileset.width;
        asset.height = tileset.height;
        asset.name = tileset.filename;

        assets.push_back(asset);
    };

    return assets;
}


bool Level::isEndOfRow(size_t index)
{
    return ((index + 1) % mapWidth == 0)
           && index != 0;
}


void Level::printPlatforms()
{
    // ----- print out the level ----- //
    using namespace std;

    const Layer& layer = layers.find("platforms")->second;
    size_t i = 0;
    int row = 0;

    cout << endl << "[" << row << "]: ";
    for (const auto& tile : layer.tiles) {
        cout << tile << " | ";
        if (this->isEndOfRow(i)) {
            ++row;
            cout << endl << "[" << row << "]:";
        }
        i++;
    }
    cout << endl << "tile count is: " << layer.tileCount << endl;
}


void printRenderData(RenderMap data)
{
    using namespace std;
    for (const auto& mapPair : data) {
        // mapPair.second - rectangles
        size_t i = 0;
        for (const auto& rectangle : mapPair.second) {
            cout << i << ": ";
            cout << "[" << rectangle.x << ", " << rectangle.y << "] " << endl;
            i++;
        }
    }
}


RenderMap Level::renderData()
{
    RenderMap map;
    // TODO: abstract
    int tileWidth = SCREEN_WIDTH / this->tilesOnScreenX;
    int tileHeight = SCREEN_HEIGHT / this->tilesOnScreenY;

    // for each asset
    // for each square to render
    // assume 1:1 LayerMap to Tileset

    // should start with the top layer, keep track of the positions on the screen that are filled
    // and skip them in the lower layers if they are filled by top layers

    // generate the clips first, rect is just the x,y and a clip id...or a gid

    for (const auto& layerPair : layers) {
        // only do platforms for now...remove this later
        if (layerPair.first == "platforms") {
            // assume only one asset for now

            // keep track of which gids have clips generated, so you don't keep generating them

            const auto& layer = layerPair.second;
            RectangleList rectangles;

            size_t i = 0; // TODO: better way to do this?
            int col = 0;
            int row = 0;
            for (const auto& tile : layer.tiles) {
                // make a rect for each of these
                // then use the GID to use the right sprite

                if (tile != 0) {
                    Rectangle rect = {};
                    rect.x = (col * tileWidth) + offsetX;
                    rect.y = (row * tileHeight) + offsetY;
                    rectangles.push_front(rect);
                }

                col++;
                if (this->isEndOfRow(i)) {
                    row++;
                    col = 0;
                }
                i++;
            }
            map[layerPair.first] = rectangles;
        }
    };
    return map;
}


void Level::scrollBy(int x, int y) {
    this->offsetX += x;
    this->offsetY += y;
}


std::list<int> Level::tilesOnScreen()
{
    int prefetch = 1; // TODO: constantize, come from options
    
    pixelsPerTileX = SCREEN_WIDTH / tilesOnScreenX;
    pixelsPerTileY = SCREEN_HEIGHT / tilesOnScreenY;
    cout << "pixels per tile: " << pixelsPerTileX;
    cout << ", " << pixelsPerTileY << endl;
    int y = offsetY / pixelsPerTileY;
    int x = offsetX / pixelsPerTileX;
    cout << "x and y: [" << x << ", " << y << "]" << endl;
    std::list<int> indices;
    
    for (int offset = x; y <= tilesOnScreenY; y++) {
        // for each row, do this
        for (; x <= tilesOnScreenX; x++) {
            // for each col
            indices.push_back(offset);
            offset += 1;
        }
        
        offset += (mapWidth - (tilesOnScreenX + prefetch)); 
    }
    Utilities::printCollection(indices);
    return indices;
}
