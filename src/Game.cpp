#include "Game.h"

Game::Game()
{

}


Game::~Game()
{

}


DrawList Game::getGameObjects()
{
    return this->gameObjects;
}


// AssetList Game::getAssets()
// {
//     // TODO: make this dynamic
//     //level.getAssets();
//     //return player.getAssets();
// }


void Game::handleInput()
{
    // FIXME: this doesn't belong here, should more into it's own thing
    // FIXME: need to allow keys to be remapped
    SDL_Event e;
    int moveSize = 8;

    //Event Polling
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            _running = false;
        }
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                _running = false;
                break;

            // -- player movement
            case SDLK_w:
                tryMovePlayer(0, -moveSize);
                break;
            case SDLK_a:
                tryMovePlayer(-moveSize, 0);
                break;
            case SDLK_s:
                tryMovePlayer(0, moveSize);
                break;
            case SDLK_d:
                tryMovePlayer(moveSize, 0);
                break;

            // -- scroll testing
            case SDLK_UP:
                level.offsetY += 1;
                break;
            case SDLK_DOWN:
                level.offsetY -= 1;
                break;
            case SDLK_LEFT:
                level.offsetX -= 1;
                break;
            case SDLK_RIGHT:
                level.offsetX += 1;
                break;

            default:
                break;
            }
        }
    }
}


void Game::tryMovePlayer(int directionX, int directionY)
{
    // using this->

    int x = playerPositionOnMap.x + directionX;
    int y = playerPositionOnMap.y + directionY;

    // Why does this have to be pixels per tile - 1 ?
    // *INDENT-OFF*
    if (level.isOpen(x, y,
                     (PIXELS_PER_TILE_X - 1),
                     (PIXELS_PER_TILE_Y - 1))) 
    {
        // move on screen
        player.move(directionX, directionY);

        // update the player's position on the level
        updatePlayerPositionBy(directionX, directionY);

        tryScrollLevel(directionX, directionY);
    }
    // *INDENT-ON*
}


void Game::tryScrollLevel(int directionX, int directionY)
{
    // --- WORKING --- //

    // this is not quite right

    // x and y screen buffer area
    // player.x() and player.y() are player position on screen
    // bufferX and screen_width - bufferX
    // also keep in mind that at the edges of the level, the
    // player will get within the buffer
    if (options.screenBufferX <
            player.x() <
            (SCREEN_WIDTH - options.screenBufferX)) {
        // can scroll left/right
        level.scrollBy(directionX, 0);
    }

    // if can scroll up/down (y)
    // scroll
    // if can scroll left/right (x)
    // scroll

}


void Game::init()
{
    if (level.loadFromJson(this->options.levelFolder) == false) {
        throw 2;
    }

    // have just loaded level
    // -- move player where level says it should be
    // FIXME: feels kind of bad to do this
    // might have to do something like this for other game drawables
    // what if it's off screen??? the following assumes it is on screen
    player.move(level.playerStartX, level.playerStartY);
    playerPositionOnMap.x = level.playerStartX;
    playerPositionOnMap.y = level.playerStartY;

    this->gameObjects.push_back(&player);
    //level.renderData();
    //try {
    //    level->init();
    //}
    //catch (int e) {
    //    throw 1;
    //}
}


void Game::load(Options options)
{
    this->options = options;
}


void Game::quit()
{
    this->_running = false;
}


void Game::teardown()
{

}


void Game::update()
{
    // gravity
    // do character updates here
    // actually do all updatables updates here
    // enemies, random moving stuff
}



void Game::updatePlayerPositionBy(int directionX, int directionY)
{
    playerPositionOnMap.x  += directionX;
    playerPositionOnMap.y += directionY;
}