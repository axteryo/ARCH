#ifndef BEAMATTACKACTION_H
#define BEAMATTACKACTION_H

#include "PhysicsComponent.h"
#include <AttackAction.h>



class BeamAttackAction : public AttackAction
{
    public:
        BeamAttackAction();
        virtual ~BeamAttackAction();
        void execute(ActorEntity* a);
        void update(ActorEntity* a);
    protected:
    private:

        //PhysicsComponent* physics_component;
};

#endif // BEAMATTACKACTION_H
