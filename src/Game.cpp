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
    // ----- this is being called twice. WHY?

    // FIXME: this doesn't belong here, should more into it's own thing
    // FIXME: need to allow keys to be remapped
    SDL_Event e;
    //int moveSize = 16;
    int moveSize = 5;

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
            case SDLK_SPACE:
                tryJumpPlayer();
                break;

            case SDLK_i:
                cout << "playerWorldId: " << playerWorldId << endl;
                break;

            default:
                break;
            }
        }

    }
}


// FIXME: remove this if it doesn't need to do anything else
void Game::tryJumpPlayer()
{
    world.tryJump(playerWorldId);
    //updatePlayerPositionBy(velocity);
}


void Game::tryMovePlayer(int directionX, int directionY)
{
    //Vector2D velocity =
    world.tryMove(playerWorldId, directionX, directionY);
    //updatePlayerPositionBy(velocity);
}


// TODO: should become a Camera class
// NOTE: really more of "update player position and level scroll on screen"
void Game::tryScrollLevel(int directionX, int directionY)
{
    int buffer =
        25; // should be larger than move size, also move into something configurable
    // Get the center of the screen for x/y
    // Attempt to scroll level if character is at that place on screen

    // FIXME: can store these instead of calculating every time
    int scrollMeridianX = (SCREEN_WIDTH / 2) - (PIXELS_PER_TILE_X / 2);
    //cout << "scroll meridianX: " << scrollMeridianX;
    //cout << " | playerx: " << player.x() << endl;
    if (player.x() >= (scrollMeridianX - buffer) &&
            (player.x() < (scrollMeridianX + buffer))) {
        if (!level.scrollByX(directionX)) {
            player.move(directionX, 0);
        }
    }
    else {
        player.move(directionX, 0);
    }

    int scrollMeridianY = (SCREEN_HEIGHT / 2) - (PIXELS_PER_TILE_Y / 2);
    //cout << "scroll meridianYX: " << scrollMeridianY;
    //cout << " | playery: " << player.y() << endl;
    if (player.y() >= (scrollMeridianY - buffer) &&
            player.y() < (scrollMeridianY + buffer)) {
        if (!level.scrollByY(directionY)) {
            player.move(0, directionY);
        }
    }
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

    world.setMap(std::make_shared<Level>(level));

    playerWorldId = world.addBody(level.playerStartX, level.playerStartY,
                                  PIXELS_PER_TILE_X, PIXELS_PER_TILE_Y);
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
    world.tick();
    updatePlayerPositionTo(world.getPosition(playerWorldId));

    // FIXME: gravity for now...
    //tryMovePlayer(0, 10);

    // do character updates here
    // actually do all updatables updates here
    // enemies, random moving stuff
}



void Game::updatePlayerPositionBy(Vector2D direction)
{
    playerPositionOnMap.x += direction.x;
    playerPositionOnMap.y += direction.y;
    //cout << "player position: " << playerPositionOnMap << endl;;

    if (!direction.isZero()) {
        //cout << "direction: " << direction << endl;
        tryScrollLevel(direction.x, direction.y);
    }

}


void Game::updatePlayerPositionTo(Point newPosition)
{
    if (playerPositionOnMap.equals(newPosition)) { return; }

    // TODO: update to use the delta method

    //cout << "updating player position to: " << newPosition << endl;
    int deltaX = newPosition.x - playerPositionOnMap.x;
    int deltaY = newPosition.y - playerPositionOnMap.y;

    //cout << "deltas: " << deltaX << " " << deltaY << endl;
    playerPositionOnMap.x = newPosition.x;
    playerPositionOnMap.y = newPosition.y;

    // if the position has changed
    if ((deltaX != 0) || (deltaY != 0)) {
        tryScrollLevel(deltaX, deltaY);
    }
}
