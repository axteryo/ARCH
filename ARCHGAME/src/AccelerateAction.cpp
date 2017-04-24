#include "AccelerateAction.h"
#include "ActorEntity.h"

AccelerateAction::AccelerateAction()
{
    //ctor
}

AccelerateAction::~AccelerateAction()
{
    //dtor
}

void AccelerateAction::execute(ActorEntity* a)
{
    float r = a->getRotation();
    States::attributeState attributes= a->getAttributes();
    b2Vec2 acceleration(0,0);

    if(attributes.accel>=attributes.accelRateLimit)
    {
        attributes.accel = attributes.accelRateLimit;
    }
    else
    {
        attributes.accel+=attributes.accelRate;

    }

    acceleration = b2Vec2(cos(r),sin(r));
    acceleration.Normalize();

    acceleration.x*=attributes.accel;
    acceleration.y*=attributes.accel;
    a->getPhysics()->accelerate(acceleration);
    a->getPhysics()->setTopSpeed(attributes.velLimit);

    a->setAttributes(attributes);

}
