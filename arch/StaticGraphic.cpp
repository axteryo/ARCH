#include "StaticGraphic.h"

StaticGraphic::StaticGraphic(sf::Texture t)
{
    texture = t;
    sprite.setTexture(texture);

}

void StaticGraphic::update(GameObject* gObj)
{
    sprite.setPosition(gObj->b2V_position.x*30, gObj->b2V_position.y*30);
    sprite.setRotation(gObj->fl_rotation);

}
sf::Sprite StaticGraphic::getSprite()
{
    return sprite;
}

StaticGraphic::~StaticGraphic()
{
    //dtor
}
