#include "LevelLoader.h"


LevelBundle
LevelLoader::loadFromJson(const string& folder)
{
    using namespace rapidjson;

    SizeType i;
    Document document;
    Level level;
    LevelBundle bundle;

    level.resPath = getResourcePath(folder);

    std::string filename = level.resPath + "level.json";
    std::string jsonString = FileHelpers::loadStringFromFile(filename);

    document.Parse(jsonString.c_str());
    assert(document.IsObject());

    LevelLoader::loadMetadata(level, document);

    const Value& layers = document["layers"];

    for (i = 0; i < layers.Size(); i++) {
        string layerName = layers[i]["name"].GetString();
        string type = layers[i]["type"].GetString();

        if (type == "tilelayer") {
            LevelLoader::loadTileLayer(level, layerName, layers[i]["data"]);
        }

        if (type == "objectgroup") {
            bundle.entities = LevelLoader::loadObjectLayer(level, layerName,
                              layers[i]["objects"]);
        }
    }

    // load tilesets
    const Value& tilesets = document["tilesets"];
    for (i = 0; i < tilesets.Size(); i++) {
        LevelLoader::loadTileset(level, tilesets[i]);
    }

    bundle.level = level;

    return bundle;
}


void LevelLoader::loadMetadata(Level& level, const rapidjson::Value& data)
{
    // using scope this->

    // TODO: write a function to accept width/height and calculate max index
    try {
        level.mapWidth = data["width"].GetInt();
        level.mapHeight = data["height"].GetInt();
        level.maxMapIndex = (level.mapHeight * level.mapWidth) - 1; // zero-indexed

        level.textureTileWidth = data["tilewidth"].GetInt();
        level.textureTileHeight = data["tileheight"].GetInt();

        // TODO: do this with the meta object layer
        level.playerStartX = stoi(data["properties"]["PlayerStartX"].GetString());
        level.playerStartY = stoi(data["properties"]["PlayerStartY"].GetString());
    }
    catch (...) {
        throw "error loading level metadata";
    }
}



// this is going to have to return entities
forward_list<Entity> LevelLoader::loadObjectLayer(Level& level,
        const string& layerName,
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

    forward_list<Entity> entities;

    try {
        for (size_t i = 0; i < data.Size(); i++) {

            // level object is drawable
            // as is entity


            Entity entity;
            entity.levelSetPosition(data[i]["x"].GetInt(), data[i]["y"].GetInt());
            entity.setSize(data[i]["width"].GetInt(), data[i]["height"].GetInt());
            entity.gid = data[i]["gid"].GetInt();
            entity.name = data[i]["name"].GetString();
            entity.visible = data[i]["visible"].GetBool();


            //level.levelObjects[object.name] = object;
            entities.push_front(entity);

            // if they are visible, add them to the background tile layer?
            // TODO: no, don't have to do this. they will be resitered as level entities
            //if (object.visible) {
            //    // subtracting one from y because Tiled positions this thing at the very edge of its cell
            //    int index = level.indexFor(object.levelX(), object.levelY() - 1);
            //    Layer& background = level.layers["background"];
            //    background.tiles[index] = object.gid;
            // }
        }
    }
    catch (...) {
        throw "error loading level object layer";
    }

    return entities;
}



void LevelLoader::loadTileLayer(Level& level, const std::string& layerName,
                                const rapidjson::Value& data)
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
    level.layers[layerName] = layer;
}


void LevelLoader::loadTileset(Level& level, const rapidjson::Value& data)
{
    // TODO: assume the filename is in the working directory, cut off the first part of the path
    using namespace rapidjson;

    std::string filename = data["image"].GetString();
    std::string layername = data["name"].GetString();
    if (filename.empty() || layername.empty()) {
        throw "could not determind layername or filename while loading tileset";
    }

    try {
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
        level.tilesets.add(layername, tileset);
    }
    catch (...) {
        throw "error loading tileset";
    }
}
