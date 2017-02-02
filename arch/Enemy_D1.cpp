#include "Enemy_D1.h"

Enemy_D1::Enemy_D1(MoveableBody* p, AnimatableGraphic* g)
{
    objectId = "object_enemy";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    b2V_acceleration = b2Vec2(0,0);
    fl_rotation = 0;
    baseState = neutral;
    secondState = unalerted;
    impactTypeState = NO_IMPACT;
    impactDirection = b2Vec2(0,0);
    topSpeed= 20;

    impactDuration = 30;

    _graphicsBody = g;
    _physicsBody = p;
    _alertRadius = new RadiusBody(300);
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

sf::Sprite Enemy_D1::getSprite()
{

    return _graphicsBody->getSprite();

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


void Enemy_D1::update()
{
    fl_rotation = _physicsBody->body->GetAngle();
    b2V_velocity = _physicsBody->body->GetLinearVelocity();
    b2Vec2 t;
    if(!targetStack.empty())
    {
        t = targetStack.top()->getPosition();
    ///Base State of ai behavior (neautral, offense, defense,
        switch(baseState)
        {
            case neutral:
                ///Secondary state of the ai.
                ///this is where the actions are initiated
                ///each base state has its own parameter of secondary states
                switch(secondState)
                {
                    case unalerted:

                    break;
                    case alerted:
                    target(t.x,t.y);

                    break;

                }


            break;
            case offense:
                switch(secondState)
                {
                    case chase:
                    target(t.x,t.y);
                    //goToward(t.x,t.y);

                    break;
                    case attacking:

                    break;





                }

            break;
            /// The basic D1 enemy doesn't have a defensive state.
            ///it's designed and geared toward relentless attacks.
            case defensive:
            switch(secondState)
            {

            }
            break;
        }
    }
    _physicsBody->applyImpact(impactTypeState,impactDirection);
    if(impactDuration<=0)
    {
        impactTypeState = NO_IMPACT;
        impactDuration = 30;
    }
    else
    {
        impactDuration-=1;
    }



    _physicsBody->update(this);
    _graphicsBody->update(this);


    b2V_acceleration = b2Vec2(0,0);

}
void Enemy_D1::setInactive()
{

}

void Enemy_D1::setNeutral()
{
    baseState = neutral;
}
void Enemy_D1::setOffense()
{
     baseState = offense;
}
void Enemy_D1::setDefensive()
{
     baseState = defensive;
}
void Enemy_D1::setUnalerted()
{
    secondState = unalerted;
}
void Enemy_D1::setAlerted()
{
    secondState = alerted;
}
void Enemy_D1::setChase()
{
    secondState = chase;
}
void Enemy_D1::setAttacking()
{
    secondState = attacking;
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

    if(!targetStack.empty())
    {
        targetStack.pop();
    }
    targetStack.push(gObj);
}

void Enemy_D1::gaugeAttack(std::string attack, b2Vec2 direction)
{
    direction.Normalize();
    impactDirection = direction;
    if(attack.compare("laser")==0)
    {
        impactTypeState = PUSHEDBACK;
    }
}

void Enemy_D1::handleCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{
    if(obj->objectId.compare("object_player")==0)
    {
        setTarget(obj);
        if(self_fixtureType.compare("alert_radius")==0)
        {

            if(fixtureType.compare("body")==0)
            {
                setOffense();
                setChase();
                //std::cout<<targetStack.size()<<std::endl;
            }
            else if(fixtureType.compare("alert_radius")==0)
            {
                setAlerted();
            }

        }
        else if(self_fixtureType.compare("body")==0)
        {
            if(fixtureType.compare("laser")==0)
            {
               gaugeAttack(fixtureType,b2Vec2(cos(obj->fl_rotation),sin(obj->fl_rotation)));
            }
        }

    }

}

