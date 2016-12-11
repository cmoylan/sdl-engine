#pragma once

#include <vector>

#include "Level.h"
#include "Player.h"


struct Options {
    int levelNumber;
    int score;
    std::string levelFolder;
};


class Game {

    Options options;
    Player player;
    Level level;

    bool _running = true;
    
public:
    
    // Getters
    std::string resPath() const { return level.resPath ;}
    bool running() const { return _running; }

    Game();
    ~Game();

    void load(Options options);
    void teardown();
    void init();
    void update();
    void handleInput();
    
    AssetList getAssets();
};
