#pragma once

#include <string>
#include <iostream>

//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 30;

const int PIXELS_PER_TILE_X = 32;
const int PIXELS_PER_TILE_Y = 32;

const std::string WINDOW_TITLE = "Game";


// Random things too small for their own file
// TODO: figure out if you can template the operator<< things
struct Vector2D {
    int x;
    int y;
    
    bool isZero() {
        return (x == 0) && (y == 0);
    }

    bool equals(Vector2D other) {
        return (x == other.x) && (y == other.y);
    }

    Vector2D delta(Vector2D other) {
        Vector2D difference = {
            x - other.x,
            y - other.y
        };
        return difference;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Vector2D& object) {
    os << "[" << object.x << ", " << object.y << "]";
    return os;
}

typedef Vector2D Point;

/* NOTES:
 * - use // *INDENT-OFF*
 *        and
 *       // *INDENT_ON*
 *   to turn off formatting. Can also use *NOPAD* for single lines.
 */
