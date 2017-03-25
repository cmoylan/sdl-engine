#pragma once

#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "file_helpers.h"
#include "res_path.h"

// TODO: fix the include path to include all subfolders
#include "../Level.h"

// TMX format loader
namespace LevelLoader
{
    /**
     * Construct a level object from a TMX map in json format
     * @param filename a string specifying the filename of the json map
     * @returns a level constructed according to the TMX json
     */
    Level loadFromJson(const std::string& filename);

    void loadMetadata(Level& level,
                      const rapidjson::Value& data);

    void loadObjectLayer(Level& level,
                         const std::string& layerName,
                         const rapidjson::Value& data);

    void loadTileLayer(Level& level,
                       const std::string& layerName,
                       const rapidjson::Value& data);

    void loadTileset(Level& level,
                     const rapidjson::Value& data);
};