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


void Game::handleInput(int tick)
{
    // ----- this is being called twice. WHY?

    // FIXME: this doesn't belong here, should more into it's own thing
    // FIXME: need to allow keys to be remapped
    SDL_Event e;
    int moveSize = 16;
    bool eventHandled = false;

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
                eventHandled = true;
                cout << "handling it!" << endl;
                break;
            case SDLK_a:
                tryMovePlayer(-moveSize, 0);
                eventHandled = true;
                break;
            case SDLK_s:
                tryMovePlayer(0, moveSize);
                cout << "tick: " << tick << endl;
                eventHandled = true;
                break;
            case SDLK_d:
                tryMovePlayer(moveSize, 0);
                eventHandled = true;
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
        // update the player's position on the level
        updatePlayerPositionBy(directionX, directionY);


        // move on screen
        //player.move(directionX, directionY);
        cout << "try move player --" << endl;
        tryScrollLevel(directionX, directionY);
    }
    // *INDENT-ON*
}


// NOTE: really more of "update player position and level scroll on screen"
void Game::tryScrollLevel(int directionX, int directionY)
{
    // --- WORKING --- //

    // kind of works, noticing some weird diagonal scrolling

    // also remove any references to level->pixelsPerTile
    // they should all go through the constant

    // if the player is in the middle of the level,
    // try to scroll it, do not move player on screen
    // if it could not scroll, move the player
    /*int scrollMeridianX = (SCREEN_WIDTH / 2) - (PIXELS_PER_TILE_X / 2);
    if (player.x() == scrollMeridianX) {
        if (not level.scrollBy(directionX, 0)) {
            player.move(directionX, 0);
        }
    }*/

    // if the player is not in the middle of the level,
    // we must be at an edge, move player on screen
    //if (player.x() != scrollMeridianX) {
    if (false) {}
    else {
        player.move(directionX, 0);
    }

    // -- do the same things but for Y
    int scrollMeridianY = (SCREEN_HEIGHT / 2) - (PIXELS_PER_TILE_Y / 2);
    if (player.y() == scrollMeridianY) {
        // getting wrong response from scrollby
        if (not level.scrollBy(0, directionY)) {
            cout << "should not be in here" << endl;
            player.move(0, directionY);
        }
        cout << "offsetx: " << level.offsetX;
//         cout << "   |   level indices: ";
//         for (auto i : level.layerIndicesOnScreen()) {
//             cout << i << ", ";
//         }
        cout << "tiles on screen y: " << level.tilesOnScreenY();
        cout << endl;
    }

    //if (player.y() != scrollMeridianY) {
    else {
        player.move(0, directionY);
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
    playerPositionOnMap.x += directionX;
    playerPositionOnMap.y += directionY;
    cout << "player map pos: " << playerPositionOnMap.x;
    cout << ", " << playerPositionOnMap.y << endl;
}