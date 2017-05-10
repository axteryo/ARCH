#include "playerInputComponent.h"




playerInputComponent::playerInputComponent()
{
}

playerInputComponent::~playerInputComponent()
{
}

void playerInputComponent::processInput(ActorEntity* a)
{
    ActionComponent* ac = a->getActions();
    if(controller.isActionKeyPressed("turnRight"))
    {
        ac->performAction("rotateRight",a);
    }
    else
    {
    }
    if(controller.isActionKeyPressed("turnLeft"))
    {
        ac->performAction("rotateLeft",a);
    }
    else
    {
    }
     if(controller.isActionKeyPressed("thrust"))
    {
        ac->performAction("accelerate",a);
    }
    else
    {
    }
     if(controller.isActionKeyPressed("brake"))
    {
        ac->performAction("brake",a);
    }
    else
    {
    }
    if(controller.isActionKeyPressed("useAttack1"))
    {
        ac->performAction("beamAttack",a);
    }
}
