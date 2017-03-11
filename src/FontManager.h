#pragma once

#include <map>
#include <string>
#include "sdl_helpers.h"

using namespace std;

class FontManager {

    string fontPath;
    map<string, TTF_Font*> fonts;

public:
    FontManager() {};
    ~FontManager();

    TTF_Font* get(string name, int size);
    const string keyFor(string name, int size);
    bool load(string name, int size);
    void setFontPath(string path);

};