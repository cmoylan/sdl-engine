#pragma once

#include <map>
#include <vector>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "file_helpers.h"
#include "res_path.h"

struct Layer {
    int tileCount;
    std::vector<int> tiles;
    int width;
    int height;
};

typedef std::map<std::string, Layer> LayerList;

class Level {

    int mapWidth;
    int mapHeight;
    int tileWidth;
    int tileHeight;

public:

    LayerList layers;

    Level();
    ~Level();

    // TODO: make this a class method that can construct a level object
    bool loadFromJson(const std::string& filename);

    void printPlatforms();

private:

    bool loadLayer(const std::string& layerName, const rapidjson::Value& data);

};