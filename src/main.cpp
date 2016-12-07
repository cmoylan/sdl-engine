#include <iostream>
#include "Game.h"

// TODO:
// - load a TMX level from json
//

int main(int, char**)
{
    Game *game = new Game();

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
