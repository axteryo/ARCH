#include "Enemy_D1.h"

Enemy_D1::Enemy_D1(MoveableBody* p, AnimatableGraphic* g)
{
    objectId = "object_enemy";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    fl_rotation = 0;
    baseState = offense;
    topSpeed= 18;

    _graphicsBody = g;
    _physicsBody = p;

    _physicsBody->body->SetUserData((void*)this);
}

Enemy_D1::~Enemy_D1()
{
    //dtor
}

void Enemy_D1::update()
{
    fl_rotation = _physicsBody->body->GetAngle();
    b2V_velocity = _physicsBody->body->GetLinearVelocity();
     switch(baseState)
    {
    case neutral:
        break;
    case offense:
        break;
    case defensive:
        break;
    }

    _physicsBody->update(this);
    _graphicsBody->update(this);
    b2V_acceleration = b2Vec2(0,0);
}

void Enemy_D1::setPosition(float x,float y)
{
    _physicsBody->body->SetTransform(b2Vec2(x/30,y/30),_physicsBody->body->GetAngle());

}
void Enemy_D1::setRotation(float angle)
{
    //fl_rotation = angle;
}

void Enemy_D1::target(float x, float y)
{
    ///first we get the location of the target
    b2Vec2 target = b2Vec2(x,y);
    ///Then we get the vector between the target and the containers position.
    b2Vec2 toTarg = target - b2V_position;
    ///Get the angle based on the vector direction toTarg
    float desiredAngle = atan2f(-toTarg.x,toTarg.y);
    float totalRotation = desiredAngle - fl_rotation;
    float change = 3*(3.141593/180);///allow 3 degrees of rotation
    while (totalRotation<-3.141592){totalRotation+=2*(3.141592);}
    while (totalRotation> 3.141592){totalRotation-=2*(3.141592);}
    fl_rotation +=std::min(change,std::max(-change, totalRotation));

}

void Enemy_D1::goToward(float x, float y)
{
    b2Vec2 direction = b2Vec2(x,y)-b2V_position;
    direction.Normalize();
    direction.x*=30;
    direction.y*=30;
    b2Vec2 steer = direction-b2V_velocity;
    steer.Normalize();
    steer.x*=.025;
    steer.y*=.025;
    b2V_acceleration+=steer;

}


void Enemy_D1::setInactive()
{

}

sf::Sprite Enemy_D1::getSprite()
{
    return _graphicsBody->getSprite();
}
