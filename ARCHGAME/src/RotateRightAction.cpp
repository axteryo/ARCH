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
    if(!isActive)
    {
        isActive = true;
    }
    elapsed+=1;


}
void RotateRightAction::update(ActorEntity* a)
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
                rate = attributes.accel_rotationRate;
            }
            else if(a->isAttacking())
            {
                if(attributes.inGridMode)
                {
                    rate = a->getAttackAttributeState().rotationRate*4;
                }
                else
                {
                    rate = a->getAttackAttributeState().rotationRate;
                }

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
}

