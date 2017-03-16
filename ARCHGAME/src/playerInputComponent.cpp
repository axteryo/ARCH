#include "playerInputComponent.h"



playerInputComponent::playerInputComponent()
{
    //ctor
}

playerInputComponent::~playerInputComponent()
{
    //dtor
}

void playerInputComponent::processInput(player* p)
{
    if(controller.isActionKeyPressed("turnRight"))
    {
        p->setTurnRightState();
    }
    else
    {
        p->setTurnRightStateFalse();
    }
    if(controller.isActionKeyPressed("turnLeft"))
    {
        p->setTurnLeftState();
    }
    else
    {
        p->setTurnLeftStateFalse();
    }
     if(controller.isActionKeyPressed("thrust"))
    {
        p->setThrustState();
    }
    else
    {
        p->setThrustStateFalse();
    }
     if(controller.isActionKeyPressed("brake"))
    {
        p->setBrakeState();
    }
    else
    {
        p->setBrakeStateFalse();
    }
}
