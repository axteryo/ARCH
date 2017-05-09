#include "RotateLeftAction.h"
#include "ActorEntity.h"

RotateLeftAction::RotateLeftAction()
{
    actionType= "rotateLeft";
    elapsed = 0;
    isActive = false;
}

RotateLeftAction::~RotateLeftAction()
{
    //dtor
}
void RotateLeftAction::execute(ActorEntity* a)
{
    elapsed+=1;
    isActive = true;
    float rate;
    StateComponent* s = a->getStates();
    PhysicsComponent* p = a->getPhysics();
    movementAttributeState attributes = s->getMovementAttributeState();

    if(attributes.accel>0)
    {
        rate = -attributes.accel_rotationRate;
    }
    else
    {
         rate = -attributes.rotationRate;
    }

    p->_rotate(rate);
    s->setMovementAttributeState(attributes);



}



