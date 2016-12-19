#include "AnimatableGraphic.h"


AnimatableGraphic::AnimatableGraphic(sf::Texture t)
{
    texture = t;
    sprite.setTexture(texture);
    height =sprite.getGlobalBounds().height;
    width = sprite.getGlobalBounds().width;
    sprite.setOrigin(width/2,height/2);

}


void AnimatableGraphic::update(Actor* container)
{
    sprite.setPosition((container->b2V_position.x*30.0), (container->b2V_position.y*30.0));
    sprite.setRotation((container->fl_rotation*(180/3.141592)));


}
void AnimatableGraphic::update(GameObject* gObj)
{
    //nothing....
}


sf::Sprite AnimatableGraphic::getSprite()
{
    return sprite;
}

AnimatableGraphic::~AnimatableGraphic()
{
    //dtor
}
