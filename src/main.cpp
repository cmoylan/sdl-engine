#include "Game.h"



int main(int, char**)
{
    Game *game = new Game();
    game->init();
    game->run();
    game->teardown();
 
    return 0;
}
