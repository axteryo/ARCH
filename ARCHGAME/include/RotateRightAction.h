#ifndef ROTATERIGHTACTION_H
#define ROTATERIGHTACTION_H

#include <Action.h>


class RotateRightAction : public Action
{
    public:
        RotateRightAction();
        virtual ~RotateRightAction();
        void execute(ActorEntity* a);
    protected:
    private:
};

#endif // ROTATERIGHTACTION_H
