#ifndef BEAMATTACKACTION_H
#define BEAMATTACKACTION_H

#include <AttackAction.h>



class BeamAttackAction : public AttackAction
{
    public:
        BeamAttackAction();
        virtual ~BeamAttackAction();
        void execute(ActorEntity* a);
        //void update(ActorEntity* a);
    protected:
    private:
};

#endif // BEAMATTACKACTION_H
