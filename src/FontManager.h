#pragma once

#include <map>
#include <string>
#include "sdl_helpers.h"

using namespace std;

class FontManager {

    /**
     * The folder where the font assets exist
     */
    string fontPath;

    /**
     * A map of font objects
     * key is the font filename and the size
     */
    map<string, TTF_Font*> fonts;

public:
    FontManager() {};
    ~FontManager();

    /**
     * Get the pointer to an opened font. Open it if it does not exist
     * @param name the font filename
     * @param size the font size
     * @returns a pointer to the TTF_Font
     */
    TTF_Font* get(string name, int size);

    /**
     * Create they key for a name/size combination
     * @param name the font filename
     * @param size the font size
     * @returns a const string that is the key for the `fonts` map
     */
    const string keyFor(string name, int size);

    /**
     * Open a font file and initialize the font
     * @param name the font filename
     * @param size the font size
     * @returns a boolean indicating if the font was loaded
     */
    bool load(string name, int size);

    /**
     * Set the path to the font directory
     * @param path the path to the font directory
     */
    void setFontPath(string path);

};