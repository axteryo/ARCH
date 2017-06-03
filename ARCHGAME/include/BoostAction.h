#ifndef BOOSTACTION_H
#define BOOSTACTION_H

#include <MovementAction.h>


class BoostAction : public MovementAction
{
    public:
        BoostAction();
        virtual ~BoostAction();
        void execute(ActorEntity* a);
        void update(ActorEntity* a);
    protected:
    private:
        float tempLimit;
        bool inCoolDown;
        int speed;
        int boostDuration;
        int boostDistance;
        b2Vec2 boostDirection;
        b2Vec2 startPos;
        b2Vec2 endPos;


};

#endif // BOOSTACTION_H
