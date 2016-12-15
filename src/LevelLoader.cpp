#include "Level.h"

bool
Level::loadFromJson(const std::string& folder)
{
    using namespace rapidjson;

    SizeType i;
    Document document;
    std::string layerName;
    this->resPath = getResourcePath(folder);
    std::string filename = this->resPath + "level.json";
    std::string jsonString = FileHelpers::loadStringFromFile(filename);

    document.Parse(jsonString.c_str());
    assert(document.IsObject());
    assert(document.HasMember("width"));

    mapWidth = document["width"].GetInt();
    mapHeight = document["height"].GetInt();
    tileWidth = document["tilewidth"].GetInt();
    tileHeight = document["tileheight"].GetInt();

    // TODO: possibly abstract
    // FIXME: these should raise exceptions, or give a more helpful error
    const Value& layers = document["layers"];
    for (i = 0; i < layers.Size(); i++) {
        layerName = layers[i]["name"].GetString();
        if (!loadLayer(layerName, layers[i]["data"])) {
            return false;
        }
    }

    // load tilesets
    const Value& tilesets = document["tilesets"];
    for (i = 0; i < tilesets.Size(); i++) {
        if (!loadTileset(tilesets[i])) {
            return false;
        }
    }

    return true;
}


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


bool    
Level::loadTileset(const rapidjson::Value& data) 
{
    using namespace rapidjson;

    std::string filename = data["image"].GetString();
    std::string layername = data["name"].GetString();
    if (filename.empty() || layername.empty()) {
      return false;
    } 

    Tileset tileset = {};
    tileset.filename = filename;
    tileset.firstGid = data["firstgid"].GetInt();
    tileset.width = data["imagewidth"].GetInt();
    tileset.height = data["imageheight"].GetInt();
    tileset.tileWidth = data["tilewidth"].GetInt();
    tileset.tileHeight = data["tileheight"].GetInt();
    tileset.setCalculatedFields();
    
    tilesets[layername] = tileset;

    return true; // TODO: actually check something was loaded
}