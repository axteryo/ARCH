#ifndef RADIUSATTACKACTION_H
#define RADIUSATTACKACTION_H

#include <AttackAction.h>


class RadiusAttackAction : public AttackAction
{
    public:
        RadiusAttackAction();
        virtual ~RadiusAttackAction();
        void execute(ActorEntity* a);
    protected:
    private:
};

#endif // RADIUSATTACKACTION_H
