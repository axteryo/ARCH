#ifndef ACCELERATEACTION_H
#define ACCELERATEACTION_H

#include <Action.h>


class AccelerateAction : public Action
{
    public:
        AccelerateAction();
        virtual ~AccelerateAction();
        void execute(ActorEntity* a);
    protected:
    private:
};

#endif // ACCELERATEACTION_H
