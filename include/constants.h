#pragma once

#include <string>

//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

const int PIXELS_PER_TILE_X = 32;
const int PIXELS_PER_TILE_Y = 32;

const std::string WINDOW_TITLE = "Game";

struct Vector2D {
    int x;
    int y;
};
