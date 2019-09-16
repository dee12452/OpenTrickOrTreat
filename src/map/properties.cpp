#include "properties.hpp"
#include "sprite/playersprite.hpp"

StairsProperty::StairsProperty(unsigned int layer)
    : layer(layer)
{}

void StairsProperty::onStep(MapSprite *sprite)
{
    sprite->setLocationZ(layer);
}
