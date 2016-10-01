#include "Player.h"

Player::Player(MoveableBody* p, AnimatableGraphic* g)
{
    objectId = "object_player";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    fl_rotation = 0;
    thrustLevel = 0;
    turnRate = .05;
    topSpeed = 12;
    thrust = false;

    _graphicsBody = g;
    _physicsBody = p;

    _physicsBody->body->SetUserData((void*)this);

    //ctor
}
void Player::update()
{
    fl_rotation = _physicsBody->body->GetAngle();

    if(rRotate)
    {
        fl_rotation+=turnRate;



    }

    if(lRotate)
    {
        fl_rotation-=turnRate;
    }

    if(thrust)
    {
        turnRate =.05;
        if(thrustLevel<2)
        {
            thrustLevel += .0075;
        }
        else{thrustLevel = 2;}

    }
    else
    {
        if(thrustLevel> 0)
        {
            thrustLevel = 0;
        }
        else{thrustLevel = 0;}

        turnRate =.1;
    }

     _physicsBody->update(this);
    _graphicsBody->update(this);
}
void Player::setPosition(float x, float y)
{
    b2V_position= b2Vec2(x/30,y/30);
}

sf::Sprite Player::getSprite()
{
    return _graphicsBody->getSprite();
}

void Player::activateThrusters()
{
    thrust = true;
}
void Player::cancelThrusters()
{
    thrust = false;
}
void Player::turnLeft()
{
    lRotate = true;
}
void Player::cancelLeftTurn()
{
    lRotate = false;
}
void Player::turnRight()
{
    rRotate = true;
}
void Player::cancelRightTurn()
{
    rRotate = false;
}
Player::~Player()
{
    //dtor
}
