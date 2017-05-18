#include "BrakeAction.h"
#include "ActorEntity.h"
BrakeAction::BrakeAction()
{
    actionType= "brake";
    elapsed = 0;
    isActive = false;
}

BrakeAction::~BrakeAction()
{
    //dtor
}

void BrakeAction::execute(ActorEntity* a)
{
    movementAttributeState attributes = a->getMovementAttributeState();
    isActive = true;
    b2Vec2 accel = a->getCurrentState().velocity;
    if(accel.Length()>=attributes.brakeLimit)
    {
        accel.x/=4;
        accel.y/=4;
        elapsed+=1;
        a->getPhysics()->accelerate(b2Vec2(-accel.x,-accel.y));
    }

 //b2Vec2 brakeVel = a->getCurrentState().velocity;
 //brakeVel.x/=2;
 //brakeVel.y/=2;
// a->getPhysics()->accelerate(brakeVel);
//setTopSpeed(attributes.brakeLimit);
}
