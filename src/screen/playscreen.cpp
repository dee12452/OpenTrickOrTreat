#include "playscreen.hpp"
#include "consumablesprite.hpp"
#include "spritefactory.hpp"

PlayScreen::PlayScreen()
    : currentMap(nullptr)
    , tileset(nullptr)
    , cameraTexture(nullptr)
    , player(nullptr)
    , hasDrawn(false)
{}

PlayScreen::~PlayScreen()
{
    if(cameraTexture)
    {
        SDL_DestroyTexture(cameraTexture);
    }
    delete currentMap;
    delete tileset;
    for(auto mapSprite : mapSprites)
    {
        delete mapSprite;
    }
    mapSprites.clear();
}

void PlayScreen::onStart(const GameState &gameState, const Window & window)
{
    tileset = new Tileset(gameState.getResourceFolderPath());
    currentMap = new Map(gameState.getResourceFolderPath(), Const::MAP_1, tileset);
    tilesetTexture = TextureManager::getInstance()->getTexture(Const::IMAGE_TOT_1);
    cameraTexture = window.createTexture(currentMap->getTilePixelWidth() * (currentMap->getCameraWidth() + 2)
            , currentMap->getTilePixelHeight() * (currentMap->getCameraHeight() + 2));
    player = new PlayerSprite(TextureManager::getInstance()->getTexture(Const::IMAGE_TOT_2));
    player->setLocationX(currentMap, currentMap->getStartLocationX() * currentMap->getTilePixelWidth());
    player->setLocationY(currentMap, currentMap->getStartLocationY() * currentMap->getTilePixelHeight());
    generateConsumables();
    generateInteractions();
    mapSprites.push_back(player);
}

void PlayScreen::onUpdate(GameState & /*gameState*/, unsigned int /*deltaTime*/)
{
    for(auto mapSprite : mapSprites)
    {
        if(mapSprite->isDisabled())
            continue;

        mapSprite->update(currentMap);
        if(hasDrawn && !mapSprite->isPlayer())
        {
            mapSprite->checkCollision(player);
        }
    }
}

void PlayScreen::onEvent(GameState & gameState, const SDL_Event & event)
{
    if(event.type == SDL_KEYDOWN)
    {
        const SDL_Scancode scancode = event.key.keysym.scancode;
        switch(scancode) 
        {
            case SDL_SCANCODE_ESCAPE:
                gameState.setState(State::STOP);
                break;
            case SDL_SCANCODE_N:
                player->toggleNoClip();
                break;
            case SDL_SCANCODE_SPACE:
                player->usePower(currentMap);
                break;
            default:
                break;
        }
    }
}

void PlayScreen::onKeyboardUpdate(GameState & /*gameState*/, const unsigned char *keyboardState)
{
    if(keyboardState[SDL_SCANCODE_UP])
    {
        player->setSpeedY(-3);
    }
    else if(keyboardState[SDL_SCANCODE_DOWN])
    {
        player->setSpeedY(3);
    }
    else if(keyboardState[SDL_SCANCODE_LEFT])
    {
        player->setSpeedX(-3);
    }
    else if(keyboardState[SDL_SCANCODE_RIGHT])
    {
        player->setSpeedX(3);
    }
    else
    {
        player->stop();
    }

    if(keyboardState[SDL_SCANCODE_LSHIFT])
    {
        if(player->getSpeedX() != 0)
        {
            player->setSpeedX(player->getSpeedX() * 5);
        }
        else
        {
            player->setSpeedY(player->getSpeedY() * 5);
        }
    }
}

void PlayScreen::onDraw(const Window & window)
{
    drawCamera(window);
}

void PlayScreen::generateConsumables()
{
    for(auto consumable : currentMap->getConsumables())
    {
        MapSprite *nextMapSprite = SpriteFactory::generateSprite(consumable);
        nextMapSprite->setLocationX(currentMap, consumable->locationX);
        nextMapSprite->setLocationY(currentMap, consumable->locationY);
        mapSprites.push_back(nextMapSprite);
    }
}

void PlayScreen::generateInteractions()
{
    for(auto interaction : currentMap->getInteractions())
    {
        MapSprite *nextMapSprite = SpriteFactory::generateSprite(interaction);
        mapSprites.push_back(nextMapSprite);
    }
}

void PlayScreen::drawCamera(const Window &window)
{
    window.setTargetTexture(cameraTexture);
    window.clear();

    const int playerTileX = player->getLocationX() / currentMap->getTileColumns();
    const int playerTileY = player->getLocationY() / currentMap->getTileRows();
    const int tileW = currentMap->getTilePixelWidth(), tileH = currentMap->getTilePixelHeight();
    const int cameraW = static_cast<int> (currentMap->getCameraWidth()) + 2;
    const int cameraH = static_cast<int> (currentMap->getCameraHeight()) + 2;
    const SDL_Rect camera = {
        playerTileX - cameraW / 2
        , playerTileY - cameraH / 2
        , cameraW
        , cameraH};

    // Draw map and players on respective layers
    for(unsigned int layerNumber = 0; layerNumber < currentMap->getNumberOfLayers(); layerNumber++)
    {
        currentMap->drawLayer(window, layerNumber, camera, tilesetTexture);
        for(auto mapSprite : mapSprites)
        {
            if(mapSprite->isDisabled())
                continue;

            mapSprite->draw(window, currentMap, camera, layerNumber);
        }
    }
    
    // Draw camera to the window
    window.resetTargetTexture();
    int offsetX = player->getLocationX() % currentMap->getTileColumns() - (player->getWidth() / 2);
    int offsetY = player->getLocationY() % currentMap->getTileRows() - (player->getHeight() / 2);
    SDL_Rect cameraSrc = {
        tileW + offsetX
        , tileH + offsetY
        , tileW * static_cast<int> (currentMap->getCameraWidth())
        , tileH * static_cast<int> (currentMap->getCameraHeight())
    };
    window.draw(cameraTexture, cameraSrc, {0, 0, Const::DEFAULT_WINDOW_WIDTH, Const::DEFAULT_WINDOW_HEIGHT});

    hasDrawn = true;
}
