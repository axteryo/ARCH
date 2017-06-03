#include "Action.h"

Action::Action()
{
    //ctor
}

Action::~Action()
{
    //dtor
}

std::string Action::getType()
{
    return actionType;
}
bool Action::getActive()
{
    return isActive;
}

void Action::cancel()
{
    elapsed = 0;
}
