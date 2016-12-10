#include <iostream>
#include "Game.h"

// TODO:
// - draw a level
//

int main(int, char**)
{
    Game game;
    
    Options opts = {
    };
    game.load(opts);

    try {
        game.init();
    }
    catch(int e) {
        std::cout << "Error initializing game!: " << e << std::endl;
        return 1;
    }

    game.run();
    game.teardown();

    return 0;
}
