#include "RotateLeftAction.h"
#include "ActorEntity.h"

RotateLeftAction::RotateLeftAction()
{
    //ctor
}

RotateLeftAction::~RotateLeftAction()
{
    //dtor
}
void RotateLeftAction::execute(ActorEntity* a)
{
    float rate;
    States::attributeState attributes = a->getAttributes();
    switch(a->accelState)
    {
    case ActorEntity::ACCELERATE:
       rate = -attributes.accel_rotationRate;
        break;
    case ActorEntity::ACCELERATE_F:
        rate = -attributes.rotationRate;
        break;
    }
   a->getPhysics()->_rotate(rate);
   a->setAttributes(attributes);
}
