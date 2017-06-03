#ifndef BRAKEACTION_H
#define BRAKEACTION_H

#include <MovementAction.h>


class BrakeAction : public MovementAction
{
    public:
        BrakeAction();
        virtual ~BrakeAction();
        void execute(ActorEntity* a);
        void update(ActorEntity* a);
    protected:
    private:
};

#endif // BRAKEACTION_H
