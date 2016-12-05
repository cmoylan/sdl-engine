#pragma once

#include <map>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "file_helpers.h"

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

    LayerList layers;

public:

    Level();
    ~Level();

    bool loadFromJson(const std::string& filename);

private:

    bool loadLayer(const std::string& layerName, const rapidjson::Value& data, int width, int height);

};