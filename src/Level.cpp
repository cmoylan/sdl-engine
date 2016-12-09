#include "Level.h"

Level::Level()
{

}


Level::~Level()
{

}


bool
Level::loadFromJson(const std::string& folder)
{
    using namespace rapidjson;

    SizeType i;
    Document document;
    std::string layerName;
    std::string filename = getResourcePath(folder).append("level.json");
    std::string jsonString = FileHelpers::loadStringFromFile(filename);

    document.Parse(jsonString.c_str());
    assert(document.IsObject());
    assert(document.HasMember("width"));

    mapWidth = document["width"].GetInt();
    mapHeight = document["height"].GetInt();
    tileWidth = document["tilewidth"].GetInt();
    tileHeight = document["tileheight"].GetInt();

    // TODO: possibly abstract
    // Using a reference for consecutive access is handy and faster.
    const Value& layers = document["layers"];
    for (i = 0; i < layers.Size(); i++) {
        layerName = layers[i]["name"].GetString();
        if (!loadLayer(layerName, layers[i]["data"])) {
            return false;
        }
    }

    // load sprites into textured
/*    const Value& tilesets = document["tilesets"];
    for (i = 0; i < tilesets.Size(); i++) {
        if (!loadTileset(tilesets[i])) {
            return false;
        }
    }   */

    return true;
}

//
bool
Level::loadLayer(const std::string& layerName, const rapidjson::Value& data)
{
    int count = 0;
    Layer layer;

    for (size_t i = 0; i < data.Size(); i++) {
        int value = data[i].GetInt();
        layer.tiles.push_back(value);

        if (value > 0) {
            count++;
        }
    }

    layer.tileCount = count;

    layers[layerName] = layer;

    // TODO: actually check that something was loaded
    return true;
}