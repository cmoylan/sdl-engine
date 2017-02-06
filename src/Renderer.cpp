#include "Renderer.h"

// FIXME: font object should be stored, rather than reopened every draw cycle
void Renderer::displayDebugInfo()
{
    const std::string resPath = getResourcePath("fonts");
    //Color is in RGBA format
    SDL_Color color = { 255, 255, 255, 255 };

    SDL_Texture *image = renderText("TTF fonts are cool!", resPath + "sample.ttf",
				    color, 16, renderer);
    if (image == nullptr){
	cleanup(renderer, window);
	TTF_Quit();
	SDL_Quit();
	// FIXME: do something bad here
	//return 1;
    }
    //Get the texture w/h so we can center it in the screen
    //int iW, iH;
    //SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    //int x = SCREEN_WIDTH / 2 - iW / 2;
    //int y = SCREEN_HEIGHT / 2 - iH / 2;
    int x = 10;
    int y = 10;

    renderTexture(image, renderer, x, y);
}


void Renderer::drawGameObjects()
{
    for (Drawable* object : game.getGameObjects()) {
        auto sprite = this->sprites[object->assetName];
        SDL_Rect clip = {};
        clip.x = 0;
        clip.y = 0;
        clip.w = 100;
        clip.h = 100;
        renderTexture(sprite.texture, renderer,
                      object->x(), object->y(), &clip);
    }
}


void Renderer::drawLevel()
{
    auto sprite = this->sprites["test-pattern-tileset.png"];
    //grass-tiles-2-small.png

    SDL_Rect clip = {};
    clip.x = 0;
    clip.y = 0;
    clip.w = 32; //SCREEN_WIDTH / game.level.tilesOnScreenX;
    clip.h = 32; //SCREEN_HEIGHT / game.level.tilesOnScreenY;

    SDL_Rect dstn = {};
    dstn.w = game.level.pixelsPerTileX;
    dstn.h = game.level.pixelsPerTileY;

    int color = 255;

    // ------- LEFT OFF HERE ------ //
    // for 1 - 6
    // draw rectangles in the right place
    // compare to the code spitting out the render data
    SDL_Rect target = {};
    target.w = SCREEN_WIDTH / 3;
    target.h = SCREEN_HEIGHT / 2;

    // works properly
    for (int i = 0; i < 6; i++) {
        target.x = (SCREEN_WIDTH / 3) * (i % 3);
        target.y = (SCREEN_HEIGHT / 2) * (i % 2);
        renderColoredRect(renderer, &target, color, 0, 0, 0);
        color -= 25;
    }



    for (const auto& renderPair : game.level.renderData()) {
        if (!RENDER_DATA_PRINTED) {
            printRenderData(game.level.renderData());
            RENDER_DATA_PRINTED = true;
        }
    //    // renderPair.first; // will be the sprite name
    //    for (const auto& rect : renderPair.second) {
    //        dstn.x = rect.x;
    //        dstn.y = rect.y;
    //        renderColoredRect(renderer, &dstn, color, 0, 0, 0);
    //        color -= 25;
    //        //renderTexture(sprite.texture, renderer,
    //        //              rect.x, rect.y, &clip);
    //
    //    }
    }
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
        for (Asset& asset : object->assetData()) {
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

    if (TTF_Init() != 0){
	logSDLError(std::cout, "TTF_Init");
	SDL_Quit();
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
    SDL_Texture* image = loadTexture(this->game.resPath() + asset.spriteFilename,
                                     renderer);
    if (image == nullptr) {
        cleanup(image, renderer, window);
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    // the naming kind of sucks here
    Sprite renderObj = {};
    renderObj.texture = image;
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
        // draw level first
        drawLevel();
        drawGameObjects();

	//displayDebugInfo();
        //renderTexture(image, renderer, x, y, &clips[useClip]);
        //renderTexture(image, renderer, player.xPos(), player.yPos(), &clips[useClip]);
        //Update the screen
        SDL_RenderPresent(renderer);
        //this->game.quit();
    }
}


void Renderer::teardown()
{
    //Clean up
    for (auto obj : sprites) {
        cleanup(obj.second.texture);
    }
    cleanup(renderer, window);
    IMG_Quit();
    SDL_Quit();
}
