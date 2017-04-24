#include "playerInputComponent.h"



playerInputComponent::playerInputComponent()
{
}

playerInputComponent::~playerInputComponent()
{
}

void playerInputComponent::processInput(ActorEntity* a)
{
    if(controller.isActionKeyPressed("turnRight"))
    {
        a->setRotateRightState();

        _rotateRight.execute(a);
    }
    else
    {
        a->setRotateRightStateFalse();
    }
    if(controller.isActionKeyPressed("turnLeft"))
    {
        a->setRotateLeftState();

        _rotateLeft.execute(a);
    }
    else
    {
        a->setRotateLeftStateFalse();
    }
     if(controller.isActionKeyPressed("thrust"))
    {
        a->setAccelState();
        _accelerate.execute(a);
    }
    else
    {
        a->setAccelStateFalse();
    }
     if(controller.isActionKeyPressed("brake"))
    {
        a->setBrakeState();
        _brake.execute(a);
    }
    else
    {
        a->setBrakeStateFalse();

    }
}
