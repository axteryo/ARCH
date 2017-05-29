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

    movementAttributeState attributes = a->getMovementAttributeState();
    if(!attributes.isBoosting)
    {
        if(attributes.isAccelerating)
        {
            rate = attributes.accel_rotationRate;
        }
        else if(a->isAttacking())
        {
            rate = a->getAttackAttributeState().rotationRate;
        }
        else
        {
             rate = attributes.rotationRate;
        }

        attributes.isRotating = true;
        a->getPhysics()->_rotate(rate);
        a->getStates()->setMovementAttributeState(attributes);
        //a->playAnimation("rotateRight",true);
    }
    else
    {
        elapsed-=1;
        isActive = false;
    }

}
void RotateRightAction::update(ActorEntity* a)
{
    elapsed-=1;
    if(elapsed<0)
    {
        movementAttributeState attributes = a->getMovementAttributeState();
        attributes.isRotating = false;
        a->getStates()->setMovementAttributeState(attributes);
        isActive = false;
        elapsed = 0;
    }
}

