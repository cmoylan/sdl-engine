#include "Level.h"


Level::Level()
{
    offsetX = 0;
    offsetY = 0;
    _tilesOnScreenX = 0;
    _tilesOnScreenY = 0;
    Color color = {15, 90, 120, 0};
    // nice brown -> RGB: 82, 23, 0
    backgroundColor = color;
}


AssetList Level::assetData()
{
    AssetList assets;
    // load assets from tilesets
    for (auto& tilesetPair : this->tilesets.all()) {
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
    // have to subtract one because of 0-indexing
    w -= 1;
    h -= 1;
    //cout << "x,y: " << valueAt(x, y);
    //cout << " | x+w,y: " << valueAt(x + w, y);
    //cout << " | x+w,y+h: " << valueAt(x + w, y + h);
    //cout << " | x, y+h: " << valueAt(x, y + h) << endl;

    // from the position get the numbers for the platforms array, check all 4 corners
    if (valueAt(x, y) == 0 &&
            valueAt(x + w, y) == 0 &&
            valueAt(x + w, y + h) == 0 &&
            valueAt(x, y + h) == 0) {
        return true;
    }
    return false;
}


// FIXME: this does not work for Y
Vector2D
Level::isOpenOrClosest(int originX, int originY,
                       int sizeW, int sizeH,
                       int velocityX, int velocityY)
{
    using namespace Utilities;

    Vector2D newVelocity = {0, 0};

    int desiredX = originX + velocityX;
    int desiredY = originY + velocityY;

    // if it's open, return desiredX/Y
    if (isOpen(desiredX, desiredY, sizeW, sizeH)) {
        newVelocity.x = velocityX;
        newVelocity.y = velocityY;
    }

    // if it's not, figure it out
    else {
        // FIXME: this bit is running even if we can't go velocity + 1, so check that first
        // start subtracting from the velocities until it's open
        while (velocityX != 0 || velocityY != 0) {
            velocityX = differenceToOrigin(velocityX, 1);
            velocityY = differenceToOrigin(velocityY, 1);
            //cout << "velocities: " << velocityX << ", " << velocityY << endl;

            if (isOpen((originX + velocityX), (originY + velocityY), sizeW, sizeH)) {
                newVelocity.x = velocityX;
                newVelocity.y = velocityY;
                break;
            }
        }
    }
    return newVelocity;
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


// ----- Rendering methods ----- //
RenderMap Level::renderData()
{
    RenderMap map;

    // should start with the top layer, keep track of the positions on the screen that are filled
    // and skip them in the lower layers if they are filled by top layers

    // generate the clips first, rect is just the x,y and a clip id...or a gid

    int renderOffsetX = screenOffsetX();
    int renderOffsetY = screenOffsetY();

    // TODO: remove when no longer needed below
    int _badX = SCREEN_WIDTH + PIXELS_PER_TILE_X;
    int _badY = SCREEN_HEIGHT + PIXELS_PER_TILE_Y;

    for (const auto& layerPair : layers) {

        // keep track of which gids have clips generated, so you don't keep generating them

        const auto& layer = layerPair.second;
        RectangleList rectangles;

        size_t i = 0; // TODO: better way to do this?
        int col = 0;
        int row = 0;

        //for (const auto& tile : layer.tiles) {
        for (auto index : this->layerIndicesOnScreen()) {
            // FIXME: reading off the end of tiles

            //
            // BUG
            // layerIndicesOnScreen is returning values higher than tiles.size()
            //

            //const auto& tile = layer.tiles[index];
            try {
                const auto& tile = layer.tiles.at(index);
                // ------------------------------------------------------------------ //
                // tile is GID
                // based on GID, get the sprite/layer
                // calculate the offset based on the w/h of the layer
                if (tile != 0) {
                    Rectangle rect = {};
                    rect.x = (col * PIXELS_PER_TILE_X) - renderOffsetX;
                    rect.y = (row * PIXELS_PER_TILE_Y) - renderOffsetY;

                    // HACK too lazy to fix this properly
                    //      the tile just off the screen is not right, so ifnore it
                    if (rect.x == _badX && rect.y == _badY) {
                        continue;
                    }
                    // END HACK

                    rect.gid = tile;
                    //rect.clipX = tileWidth;
                    //rect.clipY = tileHeight;
                    rectangles.push_front(rect);
                }
            }
            catch (...) {
                cout  << "bad index: " << index << endl;
                cout << "indices on screen: ";

                for (auto i : layerIndicesOnScreen()) {
                    cout << i << ", ";
                }
                cout << endl;
                throw - 1;
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
    };
    return map;
}
// ----- END Rendering methods ----- //


// TODO: this should be in World or Scene, not level
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
    int newOffsetX = this->offsetX + x;
    // 16
    if ((SCREEN_WIDTH + newOffsetX) < (this->mapWidth * PIXELS_PER_TILE_X)
            && (newOffsetX >= 0)) {
        this->offsetX += x;
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
        //cout << "scrolling by y: " << y << endl;
        return true;
    }
    //cout << "adding this to index: " << (mapWidth - (tilesOnScreenX() +
    //                                     tilePrefetch)) << endl;
    return false;

}



// TODO: cache this if it hasn't changed
// TODO: might want to just save tilesOnScreenX/Y as local vars, instead of calling the same method several times
list<int> Level::layerIndicesOnScreen()
{
    int index = (offsetX / PIXELS_PER_TILE_X) +
                ((offsetY / PIXELS_PER_TILE_Y) * mapWidth);
    //tilesOnScreenX()); // + tilePrefetch

    list<int> indices;

    for (int y = 0; y <= tilesOnScreenY(); y++) {
        // for each row, do this
        for (int x = 0; x <= tilesOnScreenX(); x++) {
            // for each col
            indices.push_back(index);
            index += 1;
            // stop adding if we are over the map size
            if (index > maxMapIndex) {
                goto overMaxIndex;
            }
        }
        index += (mapWidth - (tilesOnScreenX() + tilePrefetch));
        if (index > maxMapIndex) {
            goto overMaxIndex;
        }
    }
overMaxIndex:
    //Utilities::printCollection(indices);
    return indices;
}


int Level::screenOffsetX()
{
    return offsetX % PIXELS_PER_TILE_X;
}


int Level::screenOffsetY()
{
    return offsetY % PIXELS_PER_TILE_Y;

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


int Level::indexFor(Vector2D coordinates)
{
    return indexFor(coordinates.x, coordinates.y);
}


int Level::indexFor(int x, int y)
{
    // Divide by tile size to get row, col
    int row = y / PIXELS_PER_TILE_Y;
    int col = x / PIXELS_PER_TILE_X;
    int index = (row * mapWidth) + col;
    return index;
}


int Level::valueAt(int x, int y, std::string layer)
{
    int index = indexFor(x, y);
    vector<long>& tiles = layers.at(layer).tiles;
    int tile = tiles.at(index);
    return tile;
}
