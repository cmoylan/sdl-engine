#pragma once

#include "res_path.h"

#include "constants.h"
#include "Level.h"
#include "Player.h"


struct Options {
    int levelNumber;
    int score;
    std::string levelPath;
};


class Game {

    Options options;
    Player player;
    Level level;

    bool _running = true;
    
public:
    std::string resPath;

    // Getters
    bool running() const { return _running; }

    Game();
    ~Game();

    void load(Options options);
    void teardown();
    void init();
    void update();
    void handleInput();
};
