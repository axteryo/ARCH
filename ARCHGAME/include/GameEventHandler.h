#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H
#include "GameEvent.h"
#include "GameEvent_Collision.h"
#include "GameEvent_Entity.h"
#include "GameEvent_Interface.h"


class GameEventHandler
{
    public:
        GameEventHandler();
        virtual ~GameEventHandler();
        virtual void handleEvent(GameEvent* e)=0;
    protected:
    private:
};

#endif // GAMEEVENTHANDLER_H
