#ifndef BRAKEACTION_H
#define BRAKEACTION_H

#include <Action.h>


class BrakeAction : public Action
{
    public:
        BrakeAction();
        virtual ~BrakeAction();
        void execute(ActorEntity* a);
    protected:
    private:
};

#endif // BRAKEACTION_H
