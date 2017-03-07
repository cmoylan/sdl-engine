#include "Level.h"


bool
Level::loadFromJson(const std::string& folder)
{
    using namespace rapidjson;

    SizeType i;
    Document document;

    this->resPath = getResourcePath(folder);
    std::string filename = this->resPath + "level.json";
    std::string jsonString = FileHelpers::loadStringFromFile(filename);

    document.Parse(jsonString.c_str());
    assert(document.IsObject());

    this->loadMetadata(document);

    // TODO: possibly abstract
    // FIXME: these should raise exceptions, or give a more helpful error
    const Value& layers = document["layers"];
    for (i = 0; i < layers.Size(); i++) {
        std::string layerName = layers[i]["name"].GetString();
        if (!this->loadLayer(layerName, layers[i]["data"])) {
            return false;
        }
    }

    // load tilesets
    const Value& tilesets = document["tilesets"];
    for (i = 0; i < tilesets.Size(); i++) {
        if (!this->loadTileset(tilesets[i])) {
            return false;
        }
    }

    return true;
}


Level
Level::constructFromJson(const std::string& filename)
{
    Level newLevel;
    newLevel.loadFromJson(filename);
    return newLevel;
}


bool
Level::loadMetadata(const rapidjson::Value& data)
{
    // using scope this->
    assert(data.HasMember("width"));
    mapWidth = data["width"].GetInt();
    assert(data.HasMember("height"));
    mapHeight = data["height"].GetInt();

    textureTileWidth = data["tilewidth"].GetInt();
    textureTileHeight = data["tileheight"].GetInt();

    playerStartX = stoi(data["properties"]["PlayerStartX"].GetString());
    playerStartY = stoi(data["properties"]["PlayerStartY"].GetString());

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
    // TODO: assume the filename is in the working directory, cut off the first part of the path
    using namespace rapidjson;

    std::string filename = data["image"].GetString();
    std::string layername = data["name"].GetString();
    if (filename.empty() || layername.empty()) {
        return false;
    }
    filename = FileHelpers::filenameFromPath(filename);

    Tileset tileset = {};
    tileset.filename = filename;
    tileset.firstGid = data["firstgid"].GetInt();
    tileset.width = data["imagewidth"].GetInt();
    tileset.height = data["imageheight"].GetInt();
    tileset.tileWidth = data["tilewidth"].GetInt();
    tileset.tileHeight = data["tileheight"].GetInt();
    tileset.tileCount = data["tilecount"].GetInt();
    tileset.setCalculatedFields();

    tilesets[layername] = tileset;

    return true; // TODO: actually check something was loaded
}
