#include <iostream>

#include "Game.h"
#include "Renderer.h"

/* TODO:
 * - jumping
 * - store stuff in a json file so you don't have to recompile
 * - draw a level
 *   - actually draw it
 *   - consider using 64 px sprites, or even 128
 * - automate or fix anything that annoys you
 * - better exceptions
 * - smoother movement, input handling
 * - use Tiled for player sprites - set them with metadata... or somehow represent a player
 */

int main(int, char**)
{
    Renderer renderer;

    Game game;
    //std::cout << "screen w/h: " << SCREEN_WIDTH << " - " << SCREEN_HEIGHT << ": ";
    //std::cout << "tile w/h: " << SCREEN_WIDTH / 20 << " - " << SCREEN_HEIGHT / 20 <<
    //          std::endl;

    Options opts;
    opts.levelNumber = 1;
    opts.score = 0;
    opts.levelFolder = "Test Level 2";
    opts.screenBufferX = 64;
    opts.screenBufferY = 64;

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
