#include "Level.h"


Level::Level()
{
    offsetX = 0;
    offsetY = 0;
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


bool Level::isOpen(int x, int y, int w, int h)
{
    // from the position get the numbers for the platforms array, check all 4 corners
    if (valueAt(x, y) == 0 &&
            valueAt(x + w, y) == 0 &&
            valueAt(x + w, y + h) == 0 &&
            valueAt(x, y + h) == 0) {
        return true;
    }
    return false;
}


bool Level::isBlocked(int originX, int originY, int sizeW, int sizeH)
{
    return !isOpen(originX, originY, sizeW, sizeH);
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

    // TODO: calculate the x and y for the sprite

    int renderOffsetX = screenOffsetX();
    int renderOffsetY = screenOffsetY();

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

                // ------------------------------------------------------------------ //
                // tile is GID
                // based on GID, get the sprite/layer
                // calculate the offset based on the w/h of the layer
                if (tile != 0) {
                    Rectangle rect = {};
                    rect.x = (col * PIXELS_PER_TILE_X) - renderOffsetX;
                    rect.y = (row * PIXELS_PER_TILE_Y) - renderOffsetY;

                    //rect.clipX = tileWidth;
                    //rect.clipY = tileHeight;
                    rectangles.push_front(rect);
                }

                col++;
                // it's never the end of row
                // TODO: abstract into a descriptive method
                if (this->isEndOfRow(i, tilesOnScreenX() + this->tilePrefetch)) {
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


// FIXME: I don't like how this method works
// I don't think it works
bool Level::scrollBy(int x, int y)
{
    bool didScroll = false;

    if (x != 0) {
        didScroll = scrollByX(x);
    }

    if (y != 0) {
        scrollByY(y);
        didScroll = scrollByY(y) || didScroll;
    }

    return didScroll;

}


bool Level::scrollByX(int x)
{
    //cout << "inside scrollbyx" << endl;
    int newOffsetX = this->offsetX + x;
    //cout << "new offset X: " << newOffsetX << endl;
    // 16
    if ((SCREEN_WIDTH + newOffsetX) < (this->mapWidth * PIXELS_PER_TILE_X)
            && (newOffsetX >= 0)) {
        this->offsetX += x;
        //cout << "did scroll x" << endl;
        return true;
    }
    return false;
}


bool Level::scrollByY(int y)
{
    int newOffsetY = this->offsetY + y;
    //cout << "offsetY, y: " << offsetY << " " << y;
    //cout << "  |  newoffsetY: " << newOffsetY;
    //cout << "  |  screenh + new offset Y: " << SCREEN_HEIGHT + newOffsetY;
    //cout << "  |  maph * pixels: " << mapHeight * PIXELS_PER_TILE_Y << endl;
    if ((SCREEN_HEIGHT + newOffsetY) < (this->mapHeight * PIXELS_PER_TILE_Y)
            && (newOffsetY >= 0)) {
        this->offsetY += y;
        return true;
    }
    cout << "adding this to index: " << (mapWidth - (tilesOnScreenX() +
                                         tilePrefetch)) << endl;
    return false;

}



// TODO: cache this if it hasn't changed
// TODO: might want to just save tilesOnScreenX/Y as local vars, instead of calling the same method several times
std::list<int> Level::layerIndicesOnScreen()
{
    int index = (offsetX / PIXELS_PER_TILE_X) +
                ((offsetY / PIXELS_PER_TILE_Y) * mapWidth);
    //tilesOnScreenX()); // + tilePrefetch

    std::list<int> indices;

    for (int y = 0; y <= tilesOnScreenY(); y++) {
        // for each row, do this
        for (int x = 0; x <= tilesOnScreenX(); x++) {
            // for each col
            indices.push_back(index);
            index += 1;
        }
        index += (mapWidth - (tilesOnScreenX() + tilePrefetch));
        //index += ((offsetY / PIXELS_PER_TILE_Y) * tilesOnScreenX());
    }
    //Utilities::printCollection(indices);
    return indices;
}


int Level::screenOffsetX()
{
    return (offsetX % PIXELS_PER_TILE_X == 0) ? 0 : (PIXELS_PER_TILE_X / 2);
}


int Level::screenOffsetY()
{
    return (offsetY % PIXELS_PER_TILE_Y == 0) ? 0 : (PIXELS_PER_TILE_Y / 2);
}


// Determine how many tiles are on screen based on screen size
int Level::tilesOnScreenX()
{
    if (_tilesOnScreenX == 0) {
        _tilesOnScreenX = (SCREEN_WIDTH / PIXELS_PER_TILE_X) + tilePrefetch;

        // should not exceed tiles in map
        if (_tilesOnScreenX > mapWidth) {
            _tilesOnScreenX = mapWidth;
        }
    }
    return _tilesOnScreenX;
}

// Determine how many tiles are on screen based on screen size
int Level::tilesOnScreenY()
{
    if (_tilesOnScreenY == 0) {
        _tilesOnScreenY = (SCREEN_HEIGHT / PIXELS_PER_TILE_Y) + tilePrefetch;

        // should not exceed tiles in map
        if (_tilesOnScreenY > mapHeight) {
            _tilesOnScreenY = mapHeight;
        }
    }
    return _tilesOnScreenY;
}


int Level::valueAt(int x, int y, std::string layer)
{
    // Divide by tile size to get row, col
    int row = y / PIXELS_PER_TILE_Y;
    int col = x / PIXELS_PER_TILE_X;
    int index = (row * mapWidth) + col;

    vector<int>& tiles = layers.at(layer).tiles;
    int tile = tiles.at(index);
    return tile;
}
