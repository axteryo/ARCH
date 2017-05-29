#include "BoostAction.h"
#include "ActorEntity.h"

BoostAction::BoostAction()
{
    actionType= "boost";
    elapsed = 0;
    isActive = false;
    tempLimit = 0;
    boostDuration = 0;
    boostDirection = b2Vec2(0,0);
}

BoostAction::~BoostAction()
{
    //dtor
}
void BoostAction::execute(ActorEntity* a)
{
    if(!isActive)
    {
        PhysicsComponent* p = a->getPhysics();
        movementAttributeState attributes = a->getMovementAttributeState();
        elapsed+=1;
        isActive = true;
        tempLimit = a->getTopSpeed();
        int speed = tempLimit*2.5;
        p->setTopSpeed(speed);

        float r = a->getRotation();
        b2Vec2 acceleration = b2Vec2(0,0);


        attributes.accel = attributes.accelRateLimit;

        acceleration = b2Vec2(cos(r),sin(r));
        acceleration.Normalize();

        acceleration.x*=speed;//attributes.accel;
        acceleration.y*=speed;//attributes.accel;
        boostDirection =acceleration;
        //b2Vec2 antiVel = a->getCurrentState().velocity;
       // p->accelerate(antiVel);

        //attributes.isBoosting= true;
        a->getStates()->setMovementAttributeState(attributes);
        boostDuration = 5;
    }



}
void BoostAction::update(ActorEntity* a)
{
    elapsed-=1;
    if(elapsed<0)
    {
        isActive = false;
        elapsed = 0;
        a->getPhysics()->setTopSpeed(tempLimit);
        //attributes.isBoosting= false;
        //attributes.accel = 0;
        //a->getStates()->setMovementAttributeState(attributes);
    }
    if(boostDuration>0)
    {

        elapsed+=1;
        a->getPhysics()->accelerate(boostDirection);
        boostDuration-=1;

    }
    else
    {
        b2Vec2 accel = a->getCurrentState().velocity;
        if(accel.Length()>=tempLimit)
        {
        accel.x/=5;
        accel.y/=5;
        a->getPhysics()->accelerate(b2Vec2(-accel.x,-accel.y));
        elapsed+=1;
        }

    }
}
