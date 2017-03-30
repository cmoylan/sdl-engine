#include <iostream>

#include "Game.h"
#include "Renderer.h"

/* TODO:
 * - exit the level
 * - scroll to anywhere on level, for player setup
 * - message center singleton?
 * - automate or fix anything that annoys you
 * - better exceptions
 * - use Tiled for player sprites - set them with metadata... or somehow represent a player
 * - store stuff in a json file so you don't have to recompile
 * - enemies
 * - death by falling off the screen
 * - acceleration and friction when walking
 * - GUILE
 * - move camera stuff to a Scene class
 */

/* FIXME:
 *
 */

int main(int, char**)
{
    Renderer renderer;

    Game game;

    Options opts;
    opts.levelNumber = 1;
    opts.score = 0;
    opts.levelFolder = "Level 3";
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
