#include "Game.h"

Game::Game()
{

}


Game::~Game()
{

}


void Game::teardown()
{

}


void Game::handleInput()
{
    // FIXME: this doesn't belong here, should more into it's own thing
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

            case SDLK_w:
                player.move(0, 10);
                break;
            case SDLK_a:
                player.move(-10, 0);
                break;
            case SDLK_s:
                player.move(0, -10);
                break;
            case SDLK_d:
                player.move(10, 0);
                break;
            default:
                break;
            }
        }
    }
}


void Game::init()
{
    if (level.loadFromJson("Test Level") == false) {
        throw 2;
    }
    level.printPlatforms();
    try {
        //level->init();
    }
    catch (int e) {
//         std::cout << "Error initing level" << std::endl;
//         cleanup(image, renderer, window);
//         IMG_Quit();
//         SDL_Quit();
        throw 1;
    }
}


void Game::load(Options options)
{
    this->options = options;
}


void Game::run()
{
    //iW and iH are the clip width and height
    //We'll be drawing only clips so get a center position for the w/h of a clip
    int iW = 100, iH = 100;
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

    //Setup the clips for our image
    SDL_Rect clips[4];
    //Since our clips our uniform in size we can generate a list of their
    //positions using some math (the specifics of this are covered in the lesson)
    for (int i = 0; i < 4; ++i) {
        clips[i].x = i / 2 * iW;
        clips[i].y = i % 2 * iH;
        clips[i].w = iW;
        clips[i].h = iH;//Start up SDL and make sure it went ok

    }
    //Specify a default clip to start with
    int useClip = 0;
}
