#include "Player.h"

Player::Player(MoveableBody* p, AnimatableGraphic* g)
{
    objectId = "object_player";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    fl_rotation = 0;
    thrustLevel = 0;
    turnRate = .1;
    topSpeed = 12;
    thrust = false;
    rRotate= false;
    lRotate=false;

    _graphicsBody = g;
    _physicsBody = p;

    _physicsBody->body->SetUserData((void*)this);

    //ctor
}
void Player::update()
{
    fl_rotation = _physicsBody->body->GetAngle();
    b2V_velocity = _physicsBody->body->GetLinearVelocity();

    //fl_rotation = _graphicsBody->sprite.getRotation();

    if(rRotate)
    {
        fl_rotation+=turnRate;



    }

    else if(lRotate)
    {
        fl_rotation-=turnRate;
    }
    b2Vec2 aim(0,0);
    if(thrust)
    {
        turnRate =.05;
        if(thrustLevel<2)
        {
            thrustLevel += .0075;
        }
        else{thrustLevel = 2;}
        aim = b2Vec2(cos(fl_rotation),sin(fl_rotation));
        float dMag = sqrt((aim.x*aim.x)+(aim.y*aim.y));
        if(dMag!=0)
        {
            aim.x/dMag;
            aim.y/dMag;
        }

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
    aim.x*=thrustLevel;
    aim.y*=thrustLevel;

    b2V_velocity+=aim;
    if(sqrt(
            (b2V_velocity.x*b2V_velocity.x)
            +(b2V_velocity.y*b2V_velocity.y))
            >topSpeed
       )
    {
        float mag = sqrt((b2V_velocity.x*b2V_velocity.x)
                        +(b2V_velocity.y*b2V_velocity.y));
        if(mag !=0)
        {
            b2V_velocity.x/=mag;
            b2V_velocity.y/=mag;
            b2V_velocity.x*=topSpeed;
            b2V_velocity.y*=topSpeed;
        }
    }



     _physicsBody->update(this);
    _graphicsBody->update(this);
}
void Player::setPosition(float x, float y)
{
    _physicsBody->body->SetTransform(b2Vec2(x/30,y/30),_physicsBody->body->GetAngle());



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
