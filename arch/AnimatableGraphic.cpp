#include "AnimatableGraphic.h"

AnimatableGraphic::AnimatableGraphic(sf::Texture t)
{
    texture = t;
    sprite.setTexture(texture);
}

void AnimatableGraphic::update(GameObject* gObj)
{
    sprite.setPosition(gObj->b2V_position.x*30, gObj->b2V_position.y*30);
    sprite.setRotation(gObj->fl_rotation);
}

sf::Sprite AnimatableGraphic::getSprite()
{
    return sprite;
}

AnimatableGraphic::~AnimatableGraphic()
{
    //dtor
}
