#ifndef ROTATERIGHTACTION_H
#define ROTATERIGHTACTION_H

#include <MovementAction.h>


class RotateRightAction : public MovementAction
{
    public:
        RotateRightAction();
        virtual ~RotateRightAction();
        void execute(ActorEntity* a);
        void update(ActorEntity* a);

    protected:
    private:
};

#endif // ROTATERIGHTACTION_H
