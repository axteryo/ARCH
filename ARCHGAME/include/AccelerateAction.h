#ifndef ACCELERATEACTION_H
#define ACCELERATEACTION_H

#include <MovementAction.h>


class AccelerateAction : public MovementAction
{
    public:
        AccelerateAction();
        virtual ~AccelerateAction();
        void execute(ActorEntity* a);
        void update(ActorEntity* a);
    protected:
    private:
        float accel;
};

#endif // ACCELERATEACTION_H
