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
       // a->setRotateRightState();

        //_rotateRight.execute(a);
        ac->performAction("rotateRight",a);
    }
    else
    {
        //a->setRotateRightStateFalse();
    }
    if(controller.isActionKeyPressed("turnLeft"))
    {
        //a->setRotateLeftState();
        ac->performAction("rotateLeft",a);
        //_rotateLeft.execute(a);
    }
    else
    {
        //a->setRotateLeftStateFalse();
    }
     if(controller.isActionKeyPressed("thrust"))
    {
        //a->setAccelState();
        ac->performAction("accelerate",a);
        //_accelerate.execute(a);
    }
    else
    {
        //a->setAccelStateFalse();
        ac->performAction("deccelerate",a);
        //_deccelerate.execute(a);
    }
     if(controller.isActionKeyPressed("brake"))
    {
        //a->setBrakeState();
        ac->performAction("brake",a);
        //_brake.execute(a);
    }
    else
    {
        //a->setBrakeStateFalse();


    }
    if(controller.isActionKeyPressed("useAttack1"))
    {
        //a->setRotateLeftState();
        ac->performAction("beamAttack",a);
        //_rotateLeft.execute(a);
    }
}
