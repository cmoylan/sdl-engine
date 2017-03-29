#pragma once

#include <string>
#include <iostream>

//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
// TODO: need to increase this without affecting the physics
const int FPS = 30;

const int PIXELS_PER_TILE_X = 32;
const int PIXELS_PER_TILE_Y = 32;

const std::string WINDOW_TITLE = "Game";


/* NOTES:
 * - use // *INDENT-OFF*
 *        and
 *       // *INDENT_ON*
 *   to turn off formatting. Can also use *NOPAD* for single lines.
 */

struct Color {
    int r;
    int g;
    int b;
    int a;
};
