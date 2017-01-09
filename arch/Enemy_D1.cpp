#include "Enemy_D1.h"

Enemy_D1::Enemy_D1(MoveableBody* p, AnimatableGraphic* g)
{
    objectId = "object_enemy";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    b2V_acceleration = b2Vec2(0,0);
    fl_rotation = 0;
    baseState = offense;
    topSpeed= 20;

    _graphicsBody = g;
    _physicsBody = p;
    _alertRadius = new RadiusBody(600);
    _alertRadius->create(_physicsBody,"alert_radius");

    _physicsBody->body->SetUserData((void*)this);
}

Enemy_D1::~Enemy_D1()
{
    delete _alertRadius;
    delete _physicsBody;
    delete _graphicsBody;
    //dtor
}

void Enemy_D1::update()
{
    fl_rotation = _physicsBody->body->GetAngle();
    b2V_velocity = _physicsBody->body->GetLinearVelocity();
    b2Vec2 t;
     switch(baseState)
    {
    case neutral:
        break;
    case offense:
        if(!targetStack.empty())
        {
            t = targetStack.top()->getPosition();

            target(t.x,t.y);
            goToward(t.x,t.y);
        }



        break;
    case defensive:
        break;
    }


    _physicsBody->update(this);


    b2V_acceleration = b2Vec2(0,0);

}

void Enemy_D1::setPosition(float x,float y)
{
    _physicsBody->body->SetTransform(b2Vec2(x/30,y/30),_physicsBody->body->GetAngle());

}
b2Vec2 Enemy_D1::getPosition()
{
    return b2V_position;
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
    float desiredAngle = atan2f(toTarg.x,-toTarg.y);
    float totalRotation = desiredAngle - fl_rotation;
    float change = 6*(3.141593/180);///allow 6 degrees of rotation
    while (totalRotation<-3.141592){totalRotation+=2*(3.141592);}
    while (totalRotation> 3.141592){totalRotation-=2*(3.141592);}
    fl_rotation +=std::min(change,std::max(-change, totalRotation));

}

void Enemy_D1::goToward(float x, float y)
{
    b2Vec2 direction = b2Vec2(x,y)-b2V_position;
    direction.Normalize();
    direction.x*=20;
    direction.y*=20;
    b2Vec2 steer = direction-b2V_velocity;
    steer.Normalize();
    steer.x*=.4;
    steer.y*=.4;
    b2V_acceleration+=steer;

}

void Enemy_D1::setTarget(GameObject* gObj)
{
    targetStack.push(gObj);
}


void Enemy_D1::setInactive()
{

}

sf::Sprite Enemy_D1::getSprite()
{
    _graphicsBody->update(this);
    return _graphicsBody->getSprite();

}

void Enemy_D1::handleCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{
    if(obj->objectId.compare("object_player")==0)
    {
        if(fixtureType.compare("body")==0)
        {
            setTarget(obj);
            std::cout<<targetStack.size()<<std::endl;
        }

    }

}

