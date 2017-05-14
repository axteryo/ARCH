#include "RadiusAttackAction.h"

RadiusAttackAction::RadiusAttackAction()
{
    elapsed = 0;
    actionType = "";
    inCoolDown = false;
    attackFixture = nullptr;
    isActive = false;
}

RadiusAttackAction::~RadiusAttackAction()
{
    //dtor
}
void RadiusAttackAction::execute(ActorEntity* a)
{

}
