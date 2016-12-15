#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}


void Renderer::init(Game game)
{
    this->game = game;
    this->initSDL();
    this->game.init();
    
    // load assets
//     for (Asset* asset : game.getAssets()) {
//         this->registerAsset(*asset);
//     }
}


void Renderer::initSDL()
{
    //Start up SDL and make sure it went ok
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError(std::cout, "SDL_Init");
        throw 1;
    }

    //Setup our window and renderer
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        throw 1;
    }
    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        throw 1;
    }
}


// bool Renderer::registerAsset(Asset options)
// {
//     // load the asset into video memory
//     SDL_Texture* image = loadTexture(this->game.resPath() + options.spriteFilename, renderer);
//     if (image == nullptr){
//         cleanup(image, renderer, window);
//         IMG_Quit();
//         SDL_Quit();
//         return false;
//     }
//     options.sprite = image;
//     this->assets.push_back(options);
//     
//     return true;
// }


void Renderer::run()
{
    while (this->game.running()) {
        this->game.handleInput();
        this->game.update();
        
        // draw
        SDL_RenderClear(renderer);
        // foreach renderable in renderables:
        // draw
//         for (Asset asset : assets) {
//             asset.parent->what();
//             renderTexture(asset.sprite, renderer,
//                           asset.parent->x(), asset.parent->y());
//         }
        for (Drawable object : gameObjects) {
        }
        
        //renderTexture(image, renderer, x, y, &clips[useClip]);
        //renderTexture(image, renderer, player.xPos(), player.yPos(), &clips[useClip]);
        //Update the screen
        SDL_RenderPresent(renderer);
    }

    
}


void Renderer::teardown()
{
    //Clean up
    // TODO: do this for all renderables
    cleanup(renderer, window);
    IMG_Quit();
    SDL_Quit();
}
