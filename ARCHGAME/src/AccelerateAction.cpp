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
    elapsed+=1;
    isActive = true;
    float r = a->getRotation();
    b2Vec2 acceleration = b2Vec2(0,0);

    PhysicsComponent* p = a->getPhysics();
    movementAttributeState attributes = a->getMovementAttributeState();


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

}

void AccelerateAction::update(ActorEntity* a)
{
    elapsed-=1;
    if(elapsed<0)
    {
        movementAttributeState attributes = a->getMovementAttributeState();
        attributes.accel = 0;
        attributes.isAccelerating = false;
        a->getStates()->setMovementAttributeState(attributes);
        isActive = false;
        accel = 0;
        elapsed = 0;
    }
}
