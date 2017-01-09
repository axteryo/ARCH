#include "Player.h"
Player::~Player()
{

    delete _alertRadius;
    delete _physicsBody;
    delete _graphicsBody;
}

Player::Player(MoveableBody* p, AnimatableGraphic* g)
{
    objectId = "object_player";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    b2V_acceleration = b2Vec2(0,0);
    //fl_rotation = 180;
    thrustLevel = 0;
    turnRate = .1;
    topSpeed = 18;
    thrusting = false;
    rRotate= false;
    lRotate=false;

    _graphicsBody = g;
    _physicsBody = p;
    _alertRadius = new RadiusBody(300);
    _alertRadius->create(_physicsBody,"alert_radius");

    _physicsBody->body->SetUserData((void*)this);


    //ctor
}
void Player::turn()
{
    if(rRotate)
    {
        fl_rotation+=turnRate;
    }

    else if(lRotate)
    {
        fl_rotation-=turnRate;
    }

}
void Player::thrust()
{
    b2Vec2 aim(0,0);
    if(thrusting)
    {
        turnRate =.04;
        if(thrustLevel<1)
        {
            thrustLevel += .025;
        }
        else{thrustLevel = 1;}
        aim = b2Vec2(cos(fl_rotation),sin(fl_rotation));
        aim.Normalize();
        /*float dMag = sqrt((aim.x*aim.x)+(aim.y*aim.y));
        if(dMag!=0)
        {
            aim.x/=dMag;
            aim.y/=dMag;
        }*/
    }
    else
    {

        if(thrustLevel> 0)
        {  //std::cout<<"Thrust Level:"<<thrustLevel<<std::endl;
            thrustLevel = 0;
        }
        else{thrustLevel = 0;}

        turnRate =.1;
        if(sqrt(
            (b2V_velocity.x*b2V_velocity.x)
            +(b2V_velocity.y*b2V_velocity.y))>10)
           {
                b2Vec2 vel = b2V_velocity;
                vel.Normalize();
                b2V_velocity.x-=vel.x/20;
                b2V_velocity.y-=vel.y/20;

           }
    }
    aim.x*=thrustLevel;
    aim.y*=thrustLevel;
    b2V_acceleration+=aim;


}
void Player::update()
{
    fl_rotation = _physicsBody->body->GetAngle();
    b2V_velocity = _physicsBody->body->GetLinearVelocity();

    //fl_rotation = _graphicsBody->sprite.getRotation();

    ///Player turning
    turn();
    ///Player Thrusters
    thrust();






     _physicsBody->update(this);
     _graphicsBody->update(this);

     b2V_acceleration = b2Vec2(0,0);

}
void Player::setPosition(float x, float y)
{
    _physicsBody->body->SetTransform(b2Vec2(x/30,y/30),_physicsBody->body->GetAngle());



}
b2Vec2 Player::getPosition()
{
    return b2V_position;
}
void Player::setRotation(float angle)
{

    _physicsBody->body->SetTransform(_physicsBody->body->GetPosition(),angle);
}

sf::Sprite Player::getSprite()
{

    return _graphicsBody->getSprite();
}

void Player::activateThrusters()
{
    thrusting = true;
}
void Player::cancelThrusters()
{
    thrusting = false;
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

void Player::handleCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{

}
