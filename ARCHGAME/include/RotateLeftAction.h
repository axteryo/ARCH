#ifndef ROTATELEFTACTION_H
#define ROTATELEFTACTION_H

#include <MovementAction.h>


class RotateLeftAction : public MovementAction
{
    public:
        RotateLeftAction();
        virtual ~RotateLeftAction();
        void execute(ActorEntity* a);

    protected:
    private:
};

#endif // ROTATELEFTACTION_H
