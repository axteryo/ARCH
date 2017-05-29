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
        //bool inCoolDown;
        int boostDuration;
        b2Vec2 boostDirection;

};

#endif // BOOSTACTION_H
