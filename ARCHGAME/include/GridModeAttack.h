#ifndef GRIDMODEATTACK_H
#define GRIDMODEATTACK_H

#include <AttackAction.h>
#include "ActorEntity.h"



class GridModeAttack: public AttackAction
{
    public:
        GridModeAttack();
        virtual ~GridModeAttack();

        void execute(ActorEntity* a);
        void update(ActorEntity* a);
    protected:
    private:
};

#endif // GRIDMODEATTACK_H
