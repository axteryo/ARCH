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

};

#endif // BOOSTACTION_H
