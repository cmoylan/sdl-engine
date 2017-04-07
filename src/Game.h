#pragma once

#include <vector>

#include "Drawable.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Player.h"
#include "World.h"


struct Options {
    int levelNumber;
    int score;
    string levelFolder;
    //string configFile = "config.json";

    // DEPRECATED
    int screenBufferX;
    int screenBufferY;
};


class Game {

    Options options;
    Player player; // NOTE: the player is being created right here
    World world;

    //Point playerPositionOnMap;
    void updatePlayerPositionBy(Vector2D direction);
    void updatePlayerPositionTo(Point newPosition);

    int playerInputX = 0;
    int playerInputY = 0;

    size_t playerWorldId;

    DrawList gameObjects;

public:
    bool _running = true;

    Level level; // acces to this should be readonly

    // Getters
    std::string resPath() const { return level.resPath; }
    bool running() const { return _running; }

    Game();
    ~Game();

    // lifecycle methods
    void load(Options options);
    void init();
    void teardown();
    void update();
    void handleInput();
    void quit();

    // player input handlers
    void tryMovePlayer(int directionX, int directionY);
    void scrollLevelOrMovePlayer(int directionX, int directionY);

    DrawList getGameObjects();

    const string debugInfo();
};
