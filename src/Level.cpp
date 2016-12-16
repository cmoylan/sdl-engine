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
    // FIXME: use IOSTREAM
    using namespace std;
    cout << "this work?" << endl;
    // ----- print out the level ----- //
    Layer& layer = layers.find("platforms")->second;
    std::vector<int>::iterator p;
    int i, row;
    row = 0;

    printf("\n[%d]:  ", row);
    for (p = layer.tiles.begin(), i = 1; p != layer.tiles.end(); ++p, ++i) {
        printf("%d | ", *p);
        if ((i % mapWidth == 0) && (row < (mapHeight - 1))) {
            ++row;
            printf("\n[%d]:  ", row);
        }
    }
    printf("\n");
    printf("tile count is: %d\n", layer.tileCount);
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
            layerPair.second;
        }
    };
    
    return map;
}
