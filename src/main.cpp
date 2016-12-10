#include <iostream>
#include "Game.h"

// TODO:
// - draw a level
//

int main(int, char**)
{
    Options opts = {
    };
    Game *game = new Game(opts);

    try {
        game->init();
    }
    catch(int e) {
        std::cout << "Error initializing game!: " << e << std::endl;
        return 1;
    }

    game->run();
    game->teardown();

    return 0;
}
