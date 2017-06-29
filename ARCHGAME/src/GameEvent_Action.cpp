#include "GameEvent_Action.h"
#include "Action.h"
#include "entity.h"

GameEvent_Action::GameEvent_Action(Action* a,entity* e,ActionState s)
{
    event_type = EVENT_ACTION;
    _action = a;
    _entity = e;
    action_state = s;
}

GameEvent_Action::~GameEvent_Action()
{
    //dtor
}
