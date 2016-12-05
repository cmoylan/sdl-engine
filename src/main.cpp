#include <iostream>
#include "Game.h"

// TODO:
// - replace instances of printf with std::cout
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
