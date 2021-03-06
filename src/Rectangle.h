#pragma once

#include <iostream>


// FIXME: this name is not descriptive
// it's the information to render one rectangle on screen
struct Rectangle {
    int x;
    int y;
    int w;
    int h;
    int clipX;
    int clipY;
    int gid;
};

typedef std::forward_list<Rectangle> RectangleList;

// string is the asset name, rect list is where to draw them
typedef std::map<std::string, RectangleList> RenderMap;

inline std::ostream& operator<<(std::ostream& os, const Rectangle& rect)
{
    os << "[x: " << rect.x;
    os << ", y: " << rect.y;
    os << ", clipX: " << rect.clipX;
    os << ", clipY: " << rect.clipY;
    os << ", gid: " << rect.gid << "]";
    return os;
}

// TODO: move to namespace
inline void printRenderData(RenderMap data)
{
    using namespace std;
    for (const auto& mapPair : data) {
        // mapPair.second - rectangles
        size_t i = 0;
        for (const auto& rectangle : mapPair.second) {
            cout << i << ": ";
            cout << "[" << rectangle.x << ", " << rectangle.y << "] " << endl;
            i++;
        }
    }
}
