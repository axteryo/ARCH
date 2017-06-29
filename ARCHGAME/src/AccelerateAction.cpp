#include "AccelerateAction.h"
#include "ActorEntity.h"

AccelerateAction::AccelerateAction()
{
    actionType= "accelerate";
    elapsed = 0;
    isActive = false;
    accel = 0;
}

AccelerateAction::~AccelerateAction()
{
    //dtor
}

void AccelerateAction::execute(ActorEntity* a)
{
    if(!isActive)
    {
        isActive = true;
        GameEvent_Action* aEvent = new GameEvent_Action(this,a,ActionState::ACTION_INITIATE);
        a->_listener->notifyEvent(aEvent);
    }
    elapsed+=1;
}

void AccelerateAction::update(ActorEntity* a)
{
    elapsed-=1;
    movementAttributeState attributes = a->getMovementAttributeState();
    if(elapsed<0)
    {
        //movementAttributeState attributes = a->getMovementAttributeState();
        attributes.accel = 0;
        attributes.isAccelerating = false;
        a->getStates()->setMovementAttributeState(attributes);
        isActive = false;
        accel = 0;
        elapsed = 0;
    }
    else
    {
        if(!attributes.inGridMode)
        {


            float r = a->getRotation();
            b2Vec2 acceleration = b2Vec2(0,0);

            PhysicsComponent* p = a->getPhysics();

            if(accel>=attributes.accelRateLimit)
            {
                accel = attributes.accelRateLimit;

            }
            else
            {
                accel+=attributes.accelRate;

            }

            attributes.accel = accel;
            acceleration = b2Vec2(cos(r),sin(r));
            acceleration.Normalize();

            acceleration.x*=accel;
            acceleration.y*=accel;
            attributes.isAccelerating = true;
            p->accelerate(acceleration);
            p->setTopSpeed(attributes.velLimit);
            a->getStates()->setMovementAttributeState(attributes);
            GameEvent_Action* aEvent = new GameEvent_Action(this,a,ActionState::ACTION_IN_PROGRESS);
            a->_listener->notifyEvent(aEvent);
        }
    }
}
