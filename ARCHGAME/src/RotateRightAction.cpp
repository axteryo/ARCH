#include "RotateRightAction.h"
#include "ActorEntity.h"


RotateRightAction::RotateRightAction()
{
    actionType= "rotateRight";
    elapsed = 0;
    isActive = false;
}

RotateRightAction::~RotateRightAction()
{
    //dtor
}

void RotateRightAction::execute(ActorEntity* a)
{
    elapsed+=1;
    isActive = true;
    float rate;
    StateComponent* s = a->getStates();
    PhysicsComponent* p = a->getPhysics();
    movementAttributeState attributes = s->getMovementAttributeState();
    if(attributes.accel>0)
    {
        rate = attributes.accel_rotationRate;
    }
    else
    {
        rate = attributes.rotationRate;
    }

   p->_rotate(rate);
   s->setMovementAttributeState(attributes);
}

