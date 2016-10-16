#include "AnimatableGraphic.h"


AnimatableGraphic::AnimatableGraphic(sf::Texture t)
{
    texture = t;
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);

}


void AnimatableGraphic::update(GameObject* gObj)
{
    sprite.setPosition(gObj->b2V_position.x*30.0, gObj->b2V_position.y*30.0);
    sprite.setRotation((gObj->fl_rotation*(180/3.141592)));


}

sf::Sprite AnimatableGraphic::getSprite()
{
    return sprite;
}

AnimatableGraphic::~AnimatableGraphic()
{
    //dtor
}
