#include "Renderer.h"

// TODO: make generic?
void Renderer::displayDebugInfo()
{
    //Color is in RGBA format
    SDL_Color color = { 255, 255, 255, 255 };
    int fontSize = 24;
    TTF_Font* font = fonts.get("sample.ttf", fontSize);

    int x = 10;
    int y = 10;

    // for each line of the debug info,
    // make a new text texture
    stringstream message(game.debugInfo());
    string line;

    while (getline(message, line)) {
        SDL_Texture *image = renderText(line, font, color, renderer);

        if (image == nullptr) {
            cleanup(renderer, window);
            TTF_Quit();
            SDL_Quit();
            // FIXME: do something bad here
            //return 1;
        }

        renderTexture(image, renderer, x, y);
        y += fontSize;
    }
}


void Renderer::drawEntities()
{
    for (Drawable* entity : game.entities) {

        if (game.level.isOnScreen(entity->levelX(), entity->levelY(), entity->w(),
                                  entity->h())) {
            // lookup asset name if not already set
            if (entity->assetName.size() == 0) {
                entity->assetName = game.level.tilesets.assetNameFor(entity->gid);
            }

            auto sprite = this->sprites[entity->assetName];

            // llok up sprite offset
            Point spriteClipCoords = game.level.tilesets.coordinatesFor(entity->gid);

            // calculate scren pos from level pos and offset
            entity->setScreenPositionFromOffset(game.level.offsetX, game.level.offsetY);

            renderTexture(sprite.texture,
                          renderer,
                          entity->screenX(), // position on screen
                          entity->screenY(),
                          spriteClipCoords.x, // sprite clip
                          spriteClipCoords.y,
                          entity->spriteOffsetX, // this will be 32x32 for most things
                          entity->spriteOffsetY);
        }

    }
}


// FIXME: should be handled in drawGameObjects
void Renderer::drawLevel()
{
    auto spritePair = this->sprites.cbegin();
    string currentSpriteName = spritePair->first;
    Sprite sprite = spritePair->second;

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

    // do background first
    renderColoredRect(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                      game.level.backgroundColor);

    string nextSpriteName;

    for (const auto& renderPair : game.level.renderData()) {
        // renderPair.first; // will be the tileset name
        for (const auto& rect : renderPair.second) {
            dstn.x = rect.x;
            dstn.y = rect.y;

            // --- sprite switching
            // only switch if the asset has changed
            nextSpriteName = game.level.tilesets.assetNameFor(rect.gid);

            if (currentSpriteName != nextSpriteName) {
                // change the sprite
                auto it = this->sprites.find(nextSpriteName);
                if (it != this->sprites.end()) {
                    sprite = it->second;
                    currentSpriteName = nextSpriteName;
                }
                //else {
                //    this should raise an error, a sprite has not been loaded
                //}
            }

            auto tileCoords = game.level.tilesets.coordinatesFor(rect.gid);
            clip.x = tileCoords.x;
            clip.y = tileCoords.y;

            renderTexture(sprite.texture, renderer,
                          dstn.x, dstn.y, &clip);

        }
    }
    //throw -1;
}


void Renderer::drawPlayer()
{

    auto& player = game.getPlayer();
    auto sprite = this->sprites[player.assetName];

    // player will have to provide the sprite clips
    renderTexture(sprite.texture,
                  renderer,
                  player.screenX(), // position on screen
                  player.screenY(),
                  //spriteClipCoords.x, // sprite clip
                  //spriteClipCoords.y,
                  0,
                  0,
                  player.spriteOffsetX, // this will be 32x32 for most things
                  player.spriteOffsetY);
}


// TODO: renderTExt?
// renderTExt(String text,
//int x,
//int y,
//<optional stuff like size/font with reasonable defaults>)
void Renderer::drawTerminal()
{
    //Color is in RGBA format
    SDL_Color color = { 255, 255, 255, 255 };
    int fontSize = 24;
    TTF_Font* font = fonts.get("sample.ttf", fontSize);

    int x = 10;
    int y = 10;

    // for each line of the debug info,
    // make a new text texture
    stringstream message(game.terminal.text());
    string line;

    while (getline(message, line)) {
        SDL_Texture *image = renderText(line, font, color, renderer);

        if (image == nullptr) {
            cleanup(renderer, window);
            TTF_Quit();
            SDL_Quit();
            // FIXME: do something bad here
            //return 1;
        }

        renderTexture(image, renderer, x, y);
        y += fontSize;
    }
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
    for (Drawable* entity : this->game.getEntities()) {
        for (Asset& asset : entity->assetData()) {
            // TODO: do something bad if any return false
            this->registerAsset(asset);
        }
    }

    // load player
    for (Asset& asset : game.getPlayer().assetData()) {
        this->registerAsset(asset);
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

        // if terminal, render terminal
        // else render level
        if (game.currentScene == Scene::level) {
            // draw level first
            this->drawLevel();
            this->drawEntities();
            this->drawPlayer();
            this->displayDebugInfo();
        }
        else if (game.currentScene == Scene::terminal) {
            this->drawTerminal();
        }
        else {
            // menu
        }


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
