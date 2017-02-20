#include "Enemy_D1.h"

Enemy_D1::Enemy_D1(MoveableBody* p, AnimatableGraphic* g)
{
    objectId = "object_enemy";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    b2V_acceleration = b2Vec2(0,0);
    fl_rotation = 0;
    aliveState = ALIVE;
    baseState = neutral;
    secondState = unalerted;
    impactTypeState = NO_IMPACT;
    attackTypeState = NO_ATTACK;
    impactDirection = b2Vec2(0,0);
    topSpeed= 20;

    maxHealthLevel = 100;
    minHealthLevel = 0;
    currentHealthLevel = 100;
    damageAmount = 0;

    impactDuration = 30;
    attackDuration = 0;
    attackCoolDown = 0;

    _graphicsBody = g;
    _physicsBody = p;
    _alertRadius = new RadiusBody(300);
    _alertRadius->create(_physicsBody,"alert_radius");
    attackFixture = nullptr;


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
     _graphicsBody->update(this);
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
   /* b2Vec2 t;
    float fl_targetDistance;
    //secondState = actionStack.top();
    if(!targetStack.empty())
    {
        t = targetStack.top()->getPosition();
        fl_targetDistance = getDistanceFromTarget(t);

    ///Base State of ai behavior (neautral, offense, defense,
        switch(baseState)
        {
            case neutral:
                ///Secondary state of the ai.
                ///this is where the actions are initiated
                ///each base state has its own parameter of secondary states

            break;
            case offense:

            break;
            /// The basic D1 enemy doesn't have a defensive state.
            ///it's designed and geared toward relentless attacks.
            case defensive:

            break;
        }
        switch(secondState)
                {
                    case unalerted:
                    break;
                    case alerted:
                    target(t.x,t.y);
                    break;
                    case chase:
                    target(t.x,t.y);
                    goToward(t.x,t.y);
                    break;
                    case attacking:
                    break;

            }
            if(fl_targetDistance<10)
            {
                drain();

            }
            else
            {
                if(attackFixture)
                {
                _physicsBody->body->DestroyFixture(attackFixture);
                //setNoAttack();
                attackFixture = nullptr;

                }
            }

    }*/
    if(isImpacted())
    {
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
    }





    _physicsBody->update(this);



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
void Enemy_D1::arrive()
{
    if(sqrt(
        (b2V_velocity.x*b2V_velocity.x)
        +(b2V_velocity.y*b2V_velocity.y))>2)
       {
            b2Vec2 vel = b2V_velocity;
            vel.Normalize();
            b2V_velocity.x-=vel.x/10;
            b2V_velocity.y-=vel.y/10;

       }
}

void Enemy_D1::setTarget(GameObject* gObj)
{

    if(!targetStack.empty())
    {
        targetStack.pop();
    }
    targetStack.push(gObj);
}

float Enemy_D1::getDistanceFromTarget(b2Vec2 t)
{
   b2Vec2 p = getPosition();

    return sqrt(((t.x-p.x)*(t.x-p.x))+((t.y-p.y)*(t.y-p.y)));
}


void Enemy_D1::initiateCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{
       ///Checks for RADIUS interactions
        if(self_fixtureType.compare("alert_radius")==0)
        {
            if(obj->objectId.compare("object_player")==0)
            {
                setTarget(obj);
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

        }///Checks for BODY interactions
        else if(self_fixtureType.compare("body")==0)
        {

            if(fixtureType.compare("laser")==0)
            {
               gaugeAttack(fixtureType,b2Vec2(cos(obj->fl_rotation),sin(obj->fl_rotation)));
            }

        }

}
void Enemy_D1::resolveCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{

}

bool Enemy_D1::isAlive()
{
     switch(aliveState)
    {
    case ALIVE:
        return true;
        break;
    case DEAD:
        return false;
        break;
    }
}
bool Enemy_D1::isImpacted()
{
    switch(impactTypeState)
    {
         case PUSHEDBACK:
             return true;
        break;
    }

    return false;
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
void Enemy_D1::setNoAttack()
{
    attackTypeState = NO_ATTACK;
}
void Enemy_D1::useAttack(int a)
{
    if(a==1)
	{
		attackTypeState = DRAIN;
	}
}
void Enemy_D1::setDamageAmount(int a)
{
    damageAmount = a;
}
void Enemy_D1::takeDamage()
{
    currentHealthLevel -= damageAmount;
}

void Enemy_D1::drain()
{
     if(attackCoolDown<=0)
        {
        if(attackFixture)
        {
            //
            if(attackDuration<=0)
            {

                _physicsBody->body->DestroyFixture(attackFixture);
                std::cout<<"getting here"<<std::endl;
                //firing = false;
                //attackDuration = 20;
                //attackCoolDown = 60;
                setNoAttack();
                attackFixture = nullptr;

            }
            else
            {
                attackDuration-=1;
            }

        }
        else
        {
            //attackDuration = 20;
            //attackCoolDown = 60;
            //firing = true;
            b2CircleShape drainShape;
            fixtureUserData* f = new fixtureUserData;
            f->data ="drain";
            b2FixtureDef drainFixtureDef;
            drainFixtureDef.isSensor= true;
            drainShape.m_p.Set(0,0);
            drainShape.m_radius= 5;
            drainFixtureDef.shape = &drainShape;
            drainFixtureDef.userData= ((void*)f);
            attackFixture = _physicsBody->body->CreateFixture(&drainFixtureDef);

        }
    }
    else
    {
        //std::cout<<" is in cooldown"<<std::endl;
        //attackDuration = 20;
        setNoAttack();
    }

}


void Enemy_D1::handleCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{


}



