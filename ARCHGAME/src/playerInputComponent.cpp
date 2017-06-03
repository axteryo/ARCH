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

    if(controller.isActionKeyPressed("turnLeft"))
    {
        ac->performAction("rotateLeft",a);
    }
    if(controller.isActionKeyPressed("boost"))
    {
        ac->performAction("boost",a);
    }

    if(controller.isActionKeyPressed("thrust"))
    {
        ac->performAction("accelerate",a);
    }

     if(controller.isActionKeyPressed("brake"))
    {
        ac->performAction("brake",a);
    }

    if(controller.isActionKeyPressed("useAttack1"))
    {
        //ac->performAction("beamAttack",a);
    }
    if(controller.isActionKeyPressed("useAttack2"))
    {
        //ac->performAction("radiusAttack",a);
    }
    if(controller.isActionKeyPressed("useAttack3"))
    {
        //std::cout<<"getting here even a little bit"<<std::endl;
        //ac->performAction("modeAttack",a);

    }
}

void playerInputComponent::onNotifyEntityNearby(entity* e)
{

}
void playerInputComponent::onNotifyEntityWithinRadius(entity* e)
{

}
void playerInputComponent::onNotifyBodyCollision(entity* e)
{

}
