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
    
    // load level
    for (Asset tileset : this->game.level.assetData()) {
        this->registerAsset(tileset);
    }
    
    // load assets
    for (Drawable* object : this->game.getGameObjects()) {
        for (Asset& asset : object->assetData() ) {
            // TODO: do something bad if any return false
            this->registerAsset(asset);
        }
    }
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


bool Renderer::registerAsset(Asset& asset)
{
    cout << "registering: " << asset.name <<
        "  from " << asset.spriteFilename << endl;
    
    // load the asset into video memory
    SDL_Texture* image = loadTexture(this->game.resPath() + asset.spriteFilename, renderer);
    if (image == nullptr){
        cleanup(image, renderer, window);
        IMG_Quit();
        SDL_Quit();
        return false;
    }
    
    // the naming kind of sucks here
    Sprite renderObj = {};
    renderObj.sprite = image;
    renderObj.asset = asset;
    
    sprites[asset.name] = renderObj;
    
    return true;
 }


void Renderer::run()
{
    while (this->game.running()) {
        this->game.handleInput();
        this->game.update();
        
        // draw
        SDL_RenderClear(renderer);
        for (Drawable* object : game.getGameObjects()) {
                auto asset = this->sprites["player"];
                //auto asset = this->assets["ts_grass-tiles-2-small.png"];
                renderTexture(asset.sprite, renderer, 
                          object->x(), object->y());
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
    for (auto obj: sprites) {
        cleanup(obj.second.sprite);
    }
    cleanup(renderer, window);
    IMG_Quit();
    SDL_Quit();
}
