#ifndef OBSERVER_H
#define OBSERVER_H

#include "Player.h"
#include "Enemy_D1.h"
#include "GameObject.h"
#include "includes.h"

class Observer
{
    public:
        Observer();
        virtual ~Observer();
        enum GameEvent
        {
            EVENT_PLAYER_WITHIN_ATTACK_RANGE,
            EVENT_PLAYER_OUT_OF_RANGE,
            EVENT_HEALTH_BELOW_HALF,
            NOTHING
        }Game_Event;
        virtual void onNotify(GameEvent e,const GameObject& gObj) = 0;

    protected:

    private:
};


#endif // OBSERVER_H
