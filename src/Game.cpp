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
                tryMovePlayer(0, 5);
                break;
            case SDLK_a:
                tryMovePlayer(-5, 0);
                break;
            case SDLK_s:
                tryMovePlayer(0, -5);
                break;
            case SDLK_d:
                tryMovePlayer(5, 0);
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
    // TODO: predefine number of pixels per 'move'

    int x = playerPositionOnMap.x + directionX;
    int y = playerPositionOnMap.y + directionY;

    if (level.isOpen(x, y, PIXELS_PER_TILE_X, PIXELS_PER_TILE_Y)) {
        player.move(directionX, directionY);

        // update position on map!
        updatePlayerPositionBy(directionX, directionY);

        // FIXME: still needs to be written
        //level.scrollBy(directionX, directionY);
    }
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