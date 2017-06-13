#include "BoostAction.h"
#include "ActorEntity.h"

BoostAction::BoostAction()
{
    actionType= "boost";
    elapsed = 0;
    isActive = false;
    inCoolDown = false;
    tempLimit = 0;
    boostDuration = 0;
    boostDistance = 0;
    startPos = b2Vec2(0,0);
    endPos = b2Vec2(0,0);
    boostDirection = b2Vec2(0,0);
    speed = 0;
}

BoostAction::~BoostAction()
{
    //dtor
}
void BoostAction::execute(ActorEntity* a)
{
    if(!isActive)
    {
        startPos = a->getPosition();
        PhysicsComponent* p = a->getPhysics();
        movementAttributeState attributes = a->getMovementAttributeState();
        elapsed+=1;
        isActive = true;
        tempLimit = a->getTopSpeed();
        speed = tempLimit*5;
        p->setTopSpeed(speed);

        float r = a->getRotation();
        b2Vec2 acceleration = b2Vec2(0,0);


        attributes.accel = attributes.accelRateLimit;

        acceleration = b2Vec2(cos(r),sin(r));
        acceleration.Normalize();

        acceleration.x*=speed;
        acceleration.y*=speed;
        boostDirection =acceleration;
        b2Vec2 antiVel = a->getCurrentState().velocity;


        attributes.isBoosting= true;
        a->getStates()->setMovementAttributeState(attributes);
        boostDuration = 20;
        boostDistance = 1;
    }



}
void BoostAction::update(ActorEntity* a)
{
    elapsed-=1;
    movementAttributeState attributes = a->getMovementAttributeState();
    //std::cout<<"got here"<<std::endl;
    if(inCoolDown)
    {
        if(elapsed<0)
        {
            isActive = false;
            inCoolDown = false;
            elapsed = 0;
        }
    }
    else
    {
        endPos = a->getPosition();
        if(State::getDistance(startPos,endPos)<boostDistance)
        {
            elapsed+=1;
            /*if(boostDirection.Length()<=speed)
            {
                boostDirection.x*=1.5;
                boostDirection.y*=1.5;
            }*/
            a->getPhysics()->accelerate(boostDirection);

        }
        else
        {
            b2Vec2 accel = a->getCurrentState().velocity;
            if(accel.Length()>tempLimit)
            {
            accel.x/=5;
            accel.y/=5;
            a->getPhysics()->accelerate(b2Vec2(-accel.x,-accel.y));
            elapsed+=1;
            }
            else
            {
                inCoolDown = true;
                attributes.isBoosting= false;
                elapsed = 30;
                a->getPhysics()->setTopSpeed(tempLimit);
                attributes.accel = 0;
                a->getStates()->setMovementAttributeState(attributes);
            }
        }
    }
    /*if(boostDuration>0)
    {



    }*/

    if(attributes.isBraking)
    {
        cancel();
    }
}
