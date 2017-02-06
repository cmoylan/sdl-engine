#include "Level.h"


Level::Level()
{
    offsetX = 0;
    offsetY = 0;
    // TODO: comes from constants or something
    // TODO: call updatePixelsPerTile whenever these change...setter??
    tilesOnScreenX = 6;
    tilesOnScreenY = 6;
    this->updatePixelsPerTile();
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


// FIXME: not sure how to pass this->mapWidth automatically, so assume if
//        sectorWidth is 0, we want mapWidth
bool Level::isEndOfRow(size_t index, int sectorWidth)
{
    if (sectorWidth == 0) {
        sectorWidth = mapWidth;
    }
    return ((index + 1) % sectorWidth == 0)
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


// ----- Rendering methods ----- //

RenderMap Level::renderData()
{
    RenderMap map;

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

            //for (const auto& tile : layer.tiles) {
            for (auto index : this->layerIndicesOnScreen()) {
                const auto& tile = layer.tiles[index];
                // make a rect for each of these
                // then use the GID to use the right sprite

                if (tile != 0) {
                    Rectangle rect = {};
                    rect.x = (col * this->pixelsPerTileX) + offsetX;
                    rect.y = (row * this->pixelsPerTileY) + offsetY;
                    //rect.clipX = tileWidth;
                    //rect.clipY = tileHeight;
                    rectangles.push_front(rect);
                }

                col++;
                // it's never the end of row
                // TODO: abstract into a descriptive method
                if (this->isEndOfRow(i, tilesOnScreenX + tilePrefetch)) {
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

// ----- END Rendering methods ----- //


void Level::scrollBy(int x, int y)
{
    this->offsetX += x;
    this->offsetY += y;
}


void Level::updatePixelsPerTile()
{
    this->pixelsPerTileX = SCREEN_WIDTH / this->tilesOnScreenX;
    this->pixelsPerTileY = SCREEN_HEIGHT / this->tilesOnScreenY;
}


// TODO: cache this if it hasn't changed
std::list<int> Level::layerIndicesOnScreen()
{
    // FIXME: where does 20 come from? - level size?
    int index = (offsetX / pixelsPerTileX)  + ((offsetY / pixelsPerTileY) * 20);
    std::list<int> indices;

    for (int y = 0; y <= tilesOnScreenY; y++) {
        // for each row, do this
        for (int x = 0; x <= tilesOnScreenX; x++) {
            // for each col
            indices.push_back(index);
            index += 1;
        }
        index += (mapWidth - (tilesOnScreenX + tilePrefetch));
    }
    //Utilities::printCollection(indices);
    return indices;
}
