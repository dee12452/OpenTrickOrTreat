#ifndef _OPEN_TOT_MAP_SPRITE_HPP_
#define _OPEN_TOT_MAP_SPRITE_HPP_

#include "sprite.hpp"
#include "map.hpp"
#include "tileset.hpp"

class MapSprite : public Sprite
{
public:
    MapSprite(SDL_Texture *texture);
    MapSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    virtual ~MapSprite() override;

    void update(Map *currentMap);
    virtual void draw(const Window &window, Map *currentMap, const SDL_Rect &camera, unsigned int z);

    int getLocationX() const;
    void setLocationX(Map *map, int x);
    
    int getLocationY() const;
    void setLocationY(Map *map, int y);
    
    unsigned int getLocationZ() const;
    void setLocationZ(unsigned int z);

    unsigned int getMapTileX(Map *map) const;
    unsigned int getMapTileY(Map *map) const;

    int getSpeedX() const;
    void setSpeedX(int sX);
    
    int getSpeedY() const;
    void setSpeedY(int sY);

    void stopX();
    void stopY();
    
    bool isDisabled() const;
    void setDisable(bool disabled);
    
    bool isNoClip() const;
    void toggleNoClip();
    
    void checkCollision(MapSprite *otherSprite);

    virtual bool isPlayer() const;

protected:
    virtual void onUpdate(Map *currentMap);
    virtual void onChangeDirectionX(MoveDirectionX oldState, MoveDirectionX newState);
    virtual void onChangeDirectionY(MoveDirectionY oldState, MoveDirectionY newState);
    virtual void onNewTile(const Tile &oldTile, const Tile &newTile);
    virtual void onCollide(MapSprite *other);

    virtual bool canMove(Map *map) const;
    
    MoveDirectionX getCurrentDirectionX() const;
    void setCurrentDirectionX(MoveDirectionX newDirX);

    MoveDirectionY getCurrentDirectionY() const;
    void setCurrentDirectionY(MoveDirectionY newDirY);

    void setUnsafeLocationX(int x);
    void setUnsafeLocationY(int y);

private:
    void checkDirectionChanges();
    void clampLocation(Map *map);

    int locationX, locationY, locationZ; // locationZ is equivalent to which layer on the map
    int speedX, speedY;
    MoveDirectionX oldDirectionX, newDirectionX;
    MoveDirectionY oldDirectionY, newDirectionY;
    bool disabled;
    bool noClip;
};

#endif
