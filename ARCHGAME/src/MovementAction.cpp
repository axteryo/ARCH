#include "MovementAction.h"

MovementAction::MovementAction()
{
    //ctor
}

MovementAction::~MovementAction()
{
    //dtor
}

void MovementAction::update(ActorEntity* a)
{
    elapsed-=1;
    if(elapsed<0)
    {
        isActive = false;
        elapsed = 0;
    }
}

