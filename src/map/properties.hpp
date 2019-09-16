#ifndef _OPEN_TOT_PROPERTY_HPP_
#define _OPEN_TOT_PROPERTY_HPP_

class MapSprite;

class Property
{
public:
    virtual ~Property() {}

    virtual void onStep(MapSprite *sprite) = 0;
};

class StairsProperty : public Property
{
public:
    StairsProperty(unsigned int layer);

    void onStep(MapSprite *sprite) override;

private:
    unsigned int layer;
};

#endif
