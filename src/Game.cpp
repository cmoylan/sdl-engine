#include "Game.h"

Game::Game()
{

}


Game::~Game()
{

}


const string Game::debugInfo()
{
    //cout << "inside debug info " << player.screenX() << " " << player.screenY() << endl;
    string message = "player: [" + to_string(player.screenX()) +
                     ", " + to_string(player.screenY()) + "]\n";

    message += "level - offset: [" + to_string(level.offsetX) +
               ", " + to_string(level.offsetY) + "]";

    return message;
}


DrawableList& Game::getEntities()
{
    return this->entities;
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
    int moveSize = 10;

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
                playerInputY = -moveSize;
                //tryMovePlayer(0, -moveSize);
                break;
            case SDLK_a:
                playerInputX = -moveSize;
                //tryMovePlayer(-moveSize, 0);
                break;
            case SDLK_s:
                playerInputY = moveSize;
                //tryMovePlayer(0, moveSize);
                break;
            case SDLK_d:
                playerInputX = moveSize;
                //tryMovePlayer(moveSize, 0);
                break;
            case SDLK_SPACE:
                world.tryJump(playerWorldId);
                break;

            case SDLK_i:
                cout << "playerWorldId: " << playerWorldId << endl;
                break;

            default:
                break;
            }
        }

        if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s:
                playerInputY = 0;
                break;
            case SDLK_a:
            case SDLK_d:
                playerInputX = 0;
                break;
            }
        }
    }

}


void Game::tryMovePlayer(int directionX, int directionY)
{
    //Vector2D velocity =
    world.tryMove(playerWorldId, directionX, directionY);
    //updatePlayerPositionBy(velocity);
}


// TODO: should become a Camera class
// NOTE: really more of "update player position and level scroll on screen"
void Game::scrollLevelOrMovePlayer(int directionX, int directionY)
{
    int buffer =
        25; // should be larger than move size, also move into something configurable
    // Get the center of the screen for x/y
    // Attempt to scroll level if character is at that place on screen

    // FIXME: can store these instead of calculating every time
    int scrollMeridianX = (SCREEN_WIDTH / 2) - (PIXELS_PER_TILE_X / 2);
    //cout << "scroll meridianX: " << scrollMeridianX;
    //cout << " | playerx: " << player.x() << endl;
    if (player.screenX() >= (scrollMeridianX - buffer) &&
            (player.screenX() < (scrollMeridianX + buffer))) {
        //player.move();
        if (!level.scrollByX(directionX)) {
            player.screenMove(directionX, 0);
        }
    }
    else {
        player.screenMove(directionX, 0);
    }

    int scrollMeridianY = (SCREEN_HEIGHT / 2) - (PIXELS_PER_TILE_Y / 2);
    //cout << "scroll meridianYX: " << scrollMeridianY;
    //cout << " | playery: " << player.y() << endl;
    if (player.screenY() >= (scrollMeridianY - buffer) &&
            player.screenY() < (scrollMeridianY + buffer)) {
        if (!level.scrollByY(directionY)) {
            player.screenMove(0, directionY);
        }
    }
    else {
        player.screenMove(0, directionY);
    }

}


void Game::init()
{
    levelBundle = LevelLoader::loadFromJson(options.levelFolder);

    level = levelBundle.level;
    world.setMap(std::make_shared<Level>(level));

    // player is going to have to manage its animations
    // set player position from level
    player.screenSetPosition(level.playerStartX, level.playerStartY);
    player.levelSetPosition(level.playerStartX, level.playerStartY);
    player.setSize(PIXELS_PER_TILE_X, PIXELS_PER_TILE_Y);
    player.centerOn = true;
    player.assetName = "player.png";

    // add player to world
    playerWorldId = world.addBody(player.levelX(), player.levelY(),
                                  player.w(), player.h());
    //this->entities.push_back(&player);

    // add entities to world
    for (Entity& entity : levelBundle.entities) {
        int entityId = world.addBody(entity.levelX(), entity.levelY(),
                                     entity.w(), entity.h());
        entities.push_back(&entity);
    }

    cout << "got here" << endl;
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

    // move player if input is not 0
    //world.tryMove();
    world.tryMove(playerWorldId, playerInputX, playerInputY);


    world.tick();
    updatePlayerPositionTo(world.getPosition(playerWorldId));

    // FIXME: gravity for now...
    //tryMovePlayer(0, 10);

    // do character updates here
    // actually do all updatables updates here
    // enemies, random moving stuff
    messageCentre().notify();
}



void Game::updatePlayerPositionBy(Vector2D direction)
{
    player.levelMove(direction.x, direction.y);
    //playerPositionOnMap.x += direction.x;
    //playerPositionOnMap.y += direction.y;
    //cout << "player position: " << playerPositionOnMap << endl;;

    if (!direction.isZero()) {
        //cout << "direction: " << direction << endl;
        scrollLevelOrMovePlayer(direction.x, direction.y);
    }

}


void Game::updatePlayerPositionTo(Point newPosition)
{
    //if (playerPositionOnMap.equals(newPosition)) { return; }
    if (player.levelPositionEquals(newPosition.x, newPosition.y)) { return; }
    // TODO: update to use the delta method

    //cout << "updating player position to: " << newPosition << endl;
    //int deltaX = newPosition.x - playerPositionOnMap.x;
    //int deltaY = newPosition.y - playerPositionOnMap.y;
    int deltaX = newPosition.x - player.levelX();
    int deltaY = newPosition.y - player.levelY();

    //cout << "deltas: " << deltaX << " " << deltaY << endl;
    //playerPositionOnMap.x = newPosition.x;
    //playerPositionOnMap.y = newPosition.y;
    player.levelSetPosition(newPosition.x, newPosition.y);

    // if the position has changed
    if ((deltaX != 0) || (deltaY != 0)) {
        scrollLevelOrMovePlayer(deltaX, deltaY);
    }
}
