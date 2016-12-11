#include <iostream>

#include "Game.h"
#include "Renderer.h"

// TODO:
// - draw a level
// - better exceptions
//

int main(int, char**)
{
    Renderer renderer;

    Game game;

    // level number, score, level folder
    Options opts = { 1, 0, "Test Level" };
    game.load(opts);

    try {
        renderer.init(game);
    }
    catch (int e) {
        std::cout << "Error initializing game!: " << e << std::endl;
        return 1;
    }

    renderer.run();
    renderer.teardown();

    return 0;
}
