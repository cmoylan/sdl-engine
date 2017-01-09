#include <iostream>

#include "Game.h"
#include "Renderer.h"

/* TODO:
 * - draw a level
 *   - actually draw it
 * - user Catch to do some unit testing around calculations
 * - automate or fix anything that annoys you
 *   - fix struct debugger by telling a struct how to print itself
 * - better exceptions
 * - smoother scrolling, input handling
 */

int main(int, char**)
{
    Renderer renderer;

    Game game;
    //std::cout << "screen w/h: " << SCREEN_WIDTH << " - " << SCREEN_HEIGHT << ": ";
    //std::cout << "tile w/h: " << SCREEN_WIDTH / 20 << " - " << SCREEN_HEIGHT / 20 <<
    //          std::endl;

    // level number, score, level folder
    Options opts = { 1, 0, "Test Level 2" };
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
