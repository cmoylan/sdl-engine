#include "Game.h"

Game::Game()
{


}


void Game::teardown()
{
    //Clean up
    cleanup(image, renderer, window);
    IMG_Quit();
    SDL_Quit();
}


void Game::init()
{
    // ----- INIT GAME STUFF ----- //
    player = new Player();
    level = new Level();
    if (level->loadFromJson("Test Level") == false) {
        throw 2;
    }
    // ----- END INIT GAME STUFF ----- //

    // ----- INIT SDL ------ //
    //Start up SDL and make sure it went ok
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        logSDLError(std::cout, "SDL_Init");
        throw 1;
    }

    //Setup our window and renderer
    window = SDL_CreateWindow("Lesson 5", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        throw 1;
    }
    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        throw 1;
    }
    const std::string resPath = getResourcePath("Lesson5");
    image = loadTexture(resPath + "image.png", renderer);
    if (image == nullptr){
        cleanup(image, renderer, window);
        IMG_Quit();
        SDL_Quit();
        throw 1;
    }
}


void Game::render()
{

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
    for (int i = 0; i < 4; ++i){
        clips[i].x = i / 2 * iW;
        clips[i].y = i % 2 * iH;
        clips[i].w = iW;
        clips[i].h = iH;//Start up SDL and make sure it went ok

    }
    //Specify a default clip to start with
    int useClip = 0;

    // handle event
    SDL_Event e;
    bool quit = false;
    while (!quit){
        //Event Polling
        while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT){
            quit = true;
        }
        //Use number input to select which clip should be drawn
        if (e.type == SDL_KEYDOWN){
            switch (e.key.keysym.sym){
            case SDLK_1:
            case SDLK_KP_1:
                useClip = 0;
                break;
            case SDLK_2:
            case SDLK_KP_2:
                useClip = 1;
                break;
            case SDLK_3:
            case SDLK_KP_3:
                useClip = 2;
                break;
            case SDLK_4:
            case SDLK_KP_4:
                useClip = 3;
                break;
            case SDLK_ESCAPE:
                quit = true;
                break;

            case SDLK_w:
                player->move(0, 10);
                break;
            case SDLK_a:
                player->move(-10, 0);
                break;
            case SDLK_s:
                player->move(0, -10);
                break;
            case SDLK_d:
                player->move(10, 0);
                break;
            default:
                break;
            }

            // update
        }

        //Rendering
        SDL_RenderClear(renderer);
        //Draw the image
        renderTexture(image, renderer, x, y, &clips[useClip]);
        renderTexture(image, renderer, player->xPos(), player->yPos(), &clips[useClip]);
        //Update the screen
        SDL_RenderPresent(renderer);
        }

    }
}
