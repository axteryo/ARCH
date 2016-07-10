#include "AnimatableGraphic.h"

AnimatableGraphic::AnimatableGraphic(sf::Texture t)
{
    sprite.setTexture(s);
}
void AnimatableGraphic::update(GameObject* gObj)
{
    sprite.setPosition(gObj->b2V_position.x*30, gObj->b2V_position.y*30);
    sprite.setRotation(gObj->b2V_rotation);
}

sf::Sprite AnimatableGraphic::getSprite()
{
    return sprite;
}

AnimatableGraphic::~AnimatableGraphic()
{
    //dtor
}
