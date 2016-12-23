#include "Level.h"

AssetList Level::assetData()
{
    AssetList assets;
    // load assets from tilesets
    for (auto tilesetPair : this->tilesets) {
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


void
Level::printPlatforms()
{
    // ----- print out the level ----- //
    using namespace std;

    Layer& layer = layers.find("platforms")->second;
    int i, row;
    row = 0;

    cout << endl << "[" << row << "]: ";
    for (auto tile : layer.tiles) {
        cout << tile << " | ";
        if ((i % mapWidth == 0) && (row < (mapHeight - 1))) {
            ++row;
	    cout << endl << "[" << row << "]:";
        }
	i++;
    }
    cout << endl << "tile count is: " << layer.tileCount << endl;
}


RenderMap
Level::renderData()
{
    RenderMap map;
    // for each asset
    // for each square to render
    // assume 1:1 LayerMap to Tileset

    for (auto& layerPair : layers) {
        // only do platforms for now...remove this later
        if (layerPair.first == "platforms") {
            // assume only one asset for now
            auto& layer = layerPair.second;
            size_t i = 0; // TODO: better way to do this?
            for (auto tile : layer.tiles) {
              // make a rect for each of these
              // then use the GID to use the right sprite
              Rectangle rect = {};
              rect.x = i % layer.width;
              rect.y = i % layer.height;
              //rect.clipX;
              //rect.clipY;
              i++;
            }
        }
    };

    return map;
}
