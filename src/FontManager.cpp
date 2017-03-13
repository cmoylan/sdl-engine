#include "FontManager.h"

using namespace std;

FontManager::~FontManager()
{
    for (auto& fontPair : fonts) {
        auto font = fontPair.second;
        TTF_CloseFont(font);
    }
    fonts.clear();
}


TTF_Font* FontManager::get(string name, int size)
{
    // load the font if it is not found
    auto font = fonts.find(keyFor(name, size));
    if (font == fonts.end()) {
        load(name, size);
    }

    return fonts.at(keyFor(name, size));
}


const string FontManager::keyFor(string name, int size)
{
    return name + to_string(size);
}


bool FontManager::load(string name, int size)
{
    const string file = fontPath + name;

    TTF_Font *font = TTF_OpenFont(file.c_str(), size);
    if (font == nullptr) {
        logSDLError(cout, "TTF_OpenFont");
        return false;
    }

    fonts.insert(pair<string, TTF_Font*>(keyFor(name, size), font));
    cout << "loaded font: " << name << "->" << size << endl;
    return true;
}


void FontManager::setFontPath(string path)
{
    fontPath = path;
}