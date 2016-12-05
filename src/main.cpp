#include "Game.h"


int main(int, char**)
{
    Game *game = new Game();
    
    try {
        game->init();
    } 
    catch(int e) {
        printf("Error initializing game!: %d\n", e);
        return 1;
    }
    
    game->run();
    game->teardown();
 
    return 0;
}
