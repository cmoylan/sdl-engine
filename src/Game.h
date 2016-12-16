#pragma once

#include <vector>

#include "Drawable.h"
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

    bool _running = true;
    
    DrawList gameObjects;
    
public:
    
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
    void handleInput();

    DrawList getGameObjects();
    
};
