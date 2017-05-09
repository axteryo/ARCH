#ifndef DECCELERATEACTION_H
#define DECCELERATEACTION_H

#include <MovementAction.h>

class DeccelerateAction: public MovementAction
{
    public:
        DeccelerateAction();
        virtual ~DeccelerateAction();
        void execute(ActorEntity* a);
    protected:
    private:
};

#endif // DECCELERATEACTION_H
