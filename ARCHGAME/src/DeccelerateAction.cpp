#include "DeccelerateAction.h"
#include "ActorEntity.h"

DeccelerateAction::DeccelerateAction()
{
    actionType= "deccelerate";
    elapsed = 0;
    isActive = false;
}

DeccelerateAction::~DeccelerateAction()
{
    //dtor
}

void DeccelerateAction::execute(ActorEntity* a)
{
    elapsed+=1;
    isActive = true;
    StateComponent* s = a->getStates();
    movementAttributeState attributes = s->getMovementAttributeState();
    attributes.accel = 0;
    s->setMovementAttributeState(attributes);
}
