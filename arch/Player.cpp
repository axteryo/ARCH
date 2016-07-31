#include "Player.h"

Player::Player(MoveableBody* p, AnimatableGraphic* g)
{
    objectId = "object_player";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);

    _graphicsBody = g;
    _physicsBody = p;

    _physicsBody->body->SetUserData((void*)this);

    //ctor
}
void Player::update()
{
     _physicsBody->update(this);
    _graphicsBody->update(this);
}
void Player::setPosition(float x, float y)
{

}

sf::Sprite Player::getSprite()
{
    return _graphicsBody->getSprite();
}

Player::~Player()
{
    //dtor
}
