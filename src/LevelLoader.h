#pragma once

#include <string>
#include <forward_list>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "file_helpers.h"
#include "res_path.h"
#include "Entity.h"
#include "Level.h"

struct LevelBundle {
    Level level;
    forward_list<Entity> entities;
};

// TMX format loader
namespace LevelLoader
{
    /**
     * Construct a level object from a TMX map in json format
     * @param filename a string specifying the filename of the json map
     * @returns a level constructed according to the TMX json
     */
    LevelBundle loadFromJson(const std::string& filename);

    void loadMetadata(Level& level,
                      const rapidjson::Value& data);

    forward_list<Entity> loadObjectLayer(Level& level,
                                         const std::string& layerName,
                                         const rapidjson::Value& data);

    void loadTileLayer(Level& level,
                       const std::string& layerName,
                       const rapidjson::Value& data);

    void loadTileset(Level& level,
                     const rapidjson::Value& data);
};
