#include "playscreen.hpp"
#include "consumablesprite.hpp"
#include "spritefactory.hpp"

PlayScreen::PlayScreen()
    : currentMap(nullptr)
    , tileset(nullptr)
    , player(nullptr)
    , hasDrawn(false)
{}

PlayScreen::~PlayScreen()
{
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
    currentMap = new Map(window, gameState.getResourceFolderPath(), Const::MAP_1, tileset);
    player = new PlayerSprite(TextureManager::getInstance()->getTexture(Const::IMAGE_TOT_2));
    player->setLocationX(currentMap, currentMap->getStartLocationX() * currentMap->getTilePixelWidth());
    player->setLocationY(currentMap, currentMap->getStartLocationY() * currentMap->getTilePixelHeight());
    generateConsumables();
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

static int clampValue(int value, int min, int max)
{
    return std::min(std::max(value, min), max);
}

void PlayScreen::drawCamera(const Window &window)
{
    const int cameraW = (static_cast<int> (currentMap->getCameraWidth())) * currentMap->getTilePixelWidth();
    const int cameraH = (static_cast<int> (currentMap->getCameraHeight())) * currentMap->getTilePixelHeight();
    const int maxCameraX = currentMap->getTileColumns() * currentMap->getTilePixelWidth() - cameraW;
    const int maxCameraY = currentMap->getTileRows() * currentMap->getTilePixelHeight() - cameraH;
    const SDL_Rect camera = 
    {
        clampValue(player->getLocationX() - cameraW / 2, 0, maxCameraX)
        , clampValue(player->getLocationY() - cameraH / 2, 0, maxCameraY)
        , cameraW
        , cameraH
    };

    // Draw map and players on respective layers
    for(unsigned int layerNumber = 0; layerNumber < currentMap->getNumberOfLayers(); layerNumber++)
    {
        currentMap->drawLayer(
                window
                , const_cast<const Tileset *> (tileset)
                , layerNumber
                , camera);

        for(auto mapSprite : mapSprites)
        {
            if(mapSprite->isDisabled() || mapSprite->getLocationZ() != layerNumber)
                continue;

            mapSprite->draw(window, currentMap, camera);
        }
    }

    hasDrawn = true;
}
