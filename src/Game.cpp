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
        //Use number input to select which clip should be drawn
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_1:
            case SDLK_KP_1:
                //useClip = 0;
                break;
            case SDLK_2:
            case SDLK_KP_2:
                //useClip = 1;
                break;
            case SDLK_3:
            case SDLK_KP_3:
                //useClip = 2;
                break;
            case SDLK_4:
            case SDLK_KP_4:
                //useClip = 3;
                break;
            case SDLK_ESCAPE:
                _running = false;
                break;

            // player movement
            case SDLK_w:
                player.move(0, 5);
                break;
            case SDLK_a:
                player.move(-5, 0);
                break;
            case SDLK_s:
                player.move(0, -5);
                break;
            case SDLK_d:
                player.move(5, 0);
                break;

            // scroll testing
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


void Game::init()
{
    if (level.loadFromJson(this->options.levelFolder) == false) {
        throw 2;
    }

    // have just loaded level
    // -- move player where level says it should be
    // FIXME: feels kind of bad to do this
    // might have to do something like this for other game drawables
    player._x = level.playerStartX;
    player._y = level.playerStartY;

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
