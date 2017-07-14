#ifndef GAMEEVENT_ACTION_H
#define GAMEEVENT_ACTION_H


#include <GameEvent.h>
class Action;
class entity;

enum ActionState
{
    ACTION_INITIATE,
    ACTION_IN_PROGRESS,
};

class GameEvent_Action: public GameEvent
{
    public:
        GameEvent_Action(Action* a,entity* e,ActionState s);
        virtual ~GameEvent_Action();

        ActionState action_state;
        Action* _action;
        entity* _entity;
    protected:
    private:
};

#endif // GAMEEVENT_ACTION_H
