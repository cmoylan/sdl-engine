#pragma once

#include <vector>

#include "Drawable.h"
#include "Level.h"
#include "Player.h"


struct Options {
    int levelNumber;
    int score;
    std::string levelFolder;
    int screenBufferX;
    int screenBufferY;
};


class Game {

    Options options;
    Player player; // NOTE: the player is being created right here

    Point playerPositionOnMap;
    void updatePlayerPositionBy(int directionX, int directionY);


    // unused for the time being
    int playerInputX = 0;
    int playerInputY = 0;

    DrawList gameObjects;

public:
        bool _running = true;

    Level level; // acces to this should be readonly

    // Getters
    std::string resPath() const { return level.resPath ;}
    bool running() const { return _running; }

    Game();
    ~Game();

    // lifecycle methods
    void load(Options options);
    void init();
    void teardown();
    void update();
    void handleInput(int tick);
    void quit();

    void tryMovePlayer(int directionX, int directionY);
    void tryScrollLevel(int directionX, int directionY);
    DrawList getGameObjects();

};
