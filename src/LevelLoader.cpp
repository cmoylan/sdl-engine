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
        string layerName = layers[i]["name"].GetString();
        string type = layers[i]["type"].GetString();

        if (type == "tilelayer") {
            if (!this->loadTileLayer(layerName, layers[i]["data"])) {
                return false;
            }
        }

        if (type == "objectgroup") {
            this->loadObjectLayer(layerName, layers[i]["objects"]);
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

    // TODO: try/catch this as it comes from external data
    // TODO: write a function to accept width/height and calculate max index
    assert(data.HasMember("width"));
    mapWidth = data["width"].GetInt();
    assert(data.HasMember("height"));
    mapHeight = data["height"].GetInt();
    maxMapIndex = (mapHeight * mapWidth) - 1; // zero-indexed

    textureTileWidth = data["tilewidth"].GetInt();
    textureTileHeight = data["tileheight"].GetInt();

    // TODO: do this with the meta object layer
    playerStartX = stoi(data["properties"]["PlayerStartX"].GetString());
    playerStartY = stoi(data["properties"]["PlayerStartY"].GetString());

    return true;
}



void Level::loadObjectLayer(const string& layerName,
                            const rapidjson::Value& data)
{
    // "objects":[
    //     {
    //         "gid":4,
    //         "height":32,
    //         "id":5,
    //         "name":"exit",
    //         "properties": {},
    //         "rotation":0,
    //         "type":"",
    //         "visible":true,
    //         "width":32,
    //         "x":3104,
    //         "y":160
    //     }],

    for (size_t i = 0; i < data.Size(); i++) {
        LevelObject object;
        object.position = { data[i]["x"].GetInt(), data[i]["y"].GetInt() };
        object.size = { data[i]["width"].GetInt(), data[i]["height"].GetInt() };
        object.gid = data[i]["gid"].GetInt();
        object.name = data[i]["name"].GetString();
        object.visible = data[i]["visible"].GetBool();

        this->levelObjects[object.name] = object;

        // if they are visible, add them to the background tile layer?
        if (object.visible) {
            int index = indexFor(object.position);
            //cout << "index, gid of exit is: " << index << ", " << object.gid << endl;
            // FIXME: make sure this layer and index exist
            Layer& background = layers["background"];
            background.tiles[index] = object.gid;
        }
    }
}


bool
Level::loadTileLayer(const std::string& layerName, const rapidjson::Value& data)
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

    //tilesets[layername] = tileset;
    tilesets.add(layername, tileset);


    return true; // TODO: actually check something was loaded
}
