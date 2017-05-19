#include "BoostAction.h"
#include "ActorEntity.h"

BoostAction::BoostAction()
{
    actionType= "boost";
    elapsed = 0;
    isActive = false;
    tempLimit = 0;
    boostDuration = 0;
}

BoostAction::~BoostAction()
{
    //dtor
}
void BoostAction::execute(ActorEntity* a)
{
    if(!isActive)
    {
        elapsed+=1;
        isActive = true;
        tempLimit = a->getTopSpeed();
        int speed = tempLimit*1.5;
        a->getPhysics()->setTopSpeed(speed);
        boostDuration = 30;
    }



}
void BoostAction::update(ActorEntity* a)
{
    movementAttributeState attributes = a->getMovementAttributeState();
    elapsed-=1;
    if(elapsed<0)
    {
        isActive = false;
        elapsed = 0;
        a->getPhysics()->setTopSpeed(tempLimit);
        attributes.isBoosting= false;
        //attributes.accel = 0;
        a->getStates()->setMovementAttributeState(attributes);
    }
    if(boostDuration>0)
    {

        elapsed+=1;
        float r = a->getRotation();
        b2Vec2 acceleration = b2Vec2(0,0);

        PhysicsComponent* p = a->getPhysics();

        attributes.accel = attributes.accelRateLimit;


        acceleration = b2Vec2(cos(r),sin(r));
        acceleration.Normalize();

        acceleration.x*=attributes.accel;
        acceleration.y*=attributes.accel;
        p->accelerate(acceleration);
        attributes.isBoosting= true;
        a->getStates()->setMovementAttributeState(attributes);

        boostDuration-=1;

    }
    else
    {
        b2Vec2 accel = a->getCurrentState().velocity;
        if(accel.Length()>=tempLimit)
        {
        accel.x/=10;
        accel.y/=10;
        a->getPhysics()->accelerate(b2Vec2(-accel.x,-accel.y));
        elapsed+=1;
        }

    }
}
