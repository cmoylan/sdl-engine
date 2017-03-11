#include "FontManager.h"

using namespace std;

FontManager::~FontManager()
{
    for (auto fontPair : fonts) {
        auto font = fontPair->second;
        TTF_CloseFont(font);
    }
    fonts.clear();
}

TTF_Font* FontManager::get(string name, int size)
{
    // TODO: abstract out the keymaking functionality
    // probably raise exception if can't be found
    
    // modify to load if it is not found
    fonts.find(keyFor(name, size));
    // if it's std::end() load the font
    // otherwise return it
    
    return fonts.at(name + to_string(size));
    //return fonts.find(name + to_string(size))->second;
}


const string FontManager::keyFor(string name, int size)
{
    return name + to_string(size);
}


bool FontManager::load(string name, int size)
{
    const string file = fontPath + name;
    
    TTF_Font *font = TTF_OpenFont(file.c_str(), size);
    if (font == nullptr){
        logSDLError(cout, "TTF_OpenFont");
        return false;
    }
    
    fonts.insert(pair<string, TTF_Font*>(name + to_string(size), font));
    cout << "loaded font: " << name << "->" << size << endl;
    return true;
}

void FontManager::setFontPath(string path)
{
    fontPath = path;
}