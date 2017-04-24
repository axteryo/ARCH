#include "BrakeAction.h"
#include "ActorEntity.h"
BrakeAction::BrakeAction()
{
    //ctor
}

BrakeAction::~BrakeAction()
{
    //dtor
}

void BrakeAction::execute(ActorEntity* a)
{
 States::attributeState attributes = a->getAttributes();
 a->getPhysics()->setTopSpeed(attributes.brakeLimit);
}
