#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <queue>
//#include "entity.h"
//#include "SequenceEntity.h"

class GameEvent
{
    public:
        GameEvent();
        virtual ~GameEvent();
        enum eventType
        {
            EVENT_COLLISION,
            EVENT_SEQUENCE,
            EVENT_GAMESTATE,
            EVENT_ENTITY,
            EVENT_ACTION,
            EVENT_INTERFACE,
            EVENT_AUDIO
        }event_type;

        eventType getEventType();
    protected:
    private:
};

extern std::queue<GameEvent*> GameEventQueue;


#endif // GAMEEVENT_H
