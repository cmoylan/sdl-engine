#pragma once

#include <string>

//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

const int PIXELS_PER_TILE_X = 64;
const int PIXELS_PER_TILE_Y = 64;

const std::string WINDOW_TITLE = "Game";


// Random things too small for their own file
struct Vector2D {
    int x;
    int y;
};

struct Point {
    int x;
    int y;
};

/* NOTES:
 * - use // *INDENT-OFF*
 *        and
 *       // *INDENT_ON*
 *   to turn off formatting. Can also use *NOPAD* for single lines.
 */