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
    if(!isActive)
    {
        isActive = true;
    }
    elapsed+=1;
}

void RotateLeftAction::update(ActorEntity* a)
{
    elapsed-=1;
    movementAttributeState attributes = a->getMovementAttributeState();
    if(elapsed<0)
    {
        attributes.isRotating = false;
        a->getStates()->setMovementAttributeState(attributes);
        isActive = false;
        elapsed = 0;
    }
    else
    {
        float rate;
        if(!attributes.isBoosting)
        {
            if(attributes.isAccelerating)
            {
                rate = -attributes.accel_rotationRate;
            }
            else if(a->isAttacking())
            {
                if(attributes.inGridMode)
                {
                    rate = -a->getAttackAttributeState().rotationRate*4;
                }
                else
                {
                     rate = -a->getAttackAttributeState().rotationRate;
                }

            }
            else
            {
                 rate = -attributes.rotationRate;
            }

            attributes.isRotating = true;
            a->getPhysics()->_rotate(rate);
            //a->playAnimation("rotateLeft",true);
            a->getStates()->setMovementAttributeState(attributes);
        }
        else
        {
            elapsed-=1;
            isActive = false;
        }


    }
}





