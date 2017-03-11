#include "Renderer.h"

void Renderer::displayDebugInfo()
{
    //Color is in RGBA format
    SDL_Color color = { 255, 255, 255, 255 };
    TTF_Font* font = fonts.get("sample.ttf", 32);

    SDL_Texture *image = renderText(game.debugInfo(),
                                    font, color, renderer);
    if (image == nullptr) {
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
        // TODO: maybe Drawable can return a clip, or we can write a
        // render texture that accepts a generic struct with x,y,w,h - Vector2D
        SDL_Rect clip = {};
        clip.x = 0;
        clip.y = 0;
        clip.w = object->spriteOffsetX;
        clip.h = object->spriteOffsetY;
        renderTexture(sprite.texture, renderer,
                      object->x(), object->y(), &clip);
    }
}


void Renderer::drawLevel()
{
    //auto sprite = this->sprites["test-pattern-tileset.png"];
    auto sprite = this->sprites["grass-tiles-2-small.png"];

    SDL_Rect clip = {};
    clip.x = 0; // TODO: this is the position on the sprite sheet.
    clip.y = 0;
    clip.w = PIXELS_PER_TILE_X;
    clip.h = PIXELS_PER_TILE_Y;

    SDL_Rect dstn = {};
    dstn.w = PIXELS_PER_TILE_X;
    dstn.h = PIXELS_PER_TILE_Y;


    if (!RENDER_DATA_PRINTED) {
        printRenderData(game.level.renderData());
        cout << "tiles on screen X: " << game.level.tilesOnScreenX() << endl;
        cout << "tiles on screen Y: " << game.level.tilesOnScreenY() << endl;
        RENDER_DATA_PRINTED = true;
    }

    for (const auto& renderPair : game.level.renderData()) {
        // renderPair.first; // will be the sprite name
        for (const auto& rect : renderPair.second) {
            dstn.x = rect.x;
            dstn.y = rect.y;
            //renderColoredRect(renderer, &dstn, r, g, b, 0);

            renderTexture(sprite.texture, renderer,
                          dstn.x, dstn.y, &clip);

        }
    }
    displayDebugInfo();
}


// this might be a load, not an init
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

    // load fonts
    fonts.setFontPath(getResourcePath("fonts"));
    //fonts.load("sample.ttf", 32);
}


void Renderer::initSDL()
{
    //Start up SDL and make sure it went ok
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError(std::cout, "SDL_Init");
        throw 1;
    }

    if (TTF_Init() != 0) {
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
    cout << "- success!" << endl;

    // the naming kind of sucks here
    Sprite renderObj = {};
    renderObj.texture = image;
    renderObj.asset = asset;

    sprites[asset.name] = renderObj;

    return true;
}


void Renderer::run()
{
    Uint32 startTime;
    int tick = 0;

    while (this->game.running()) {
        if (tick > 9) {
            tick = 0;
        }

        startTime = SDL_GetTicks();

        this->game.handleInput();
        this->game.update();

        // draw
        SDL_RenderClear(renderer);
        // draw level first
        this->drawLevel();
        this->drawGameObjects();

        //displayDebugInfo();
        //Update the screen
        SDL_RenderPresent(renderer);
        //this->game.quit();

        if (1000 / FPS > SDL_GetTicks() - startTime) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - startTime));
        }

        tick += 1;
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
