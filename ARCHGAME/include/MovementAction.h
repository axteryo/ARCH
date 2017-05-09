#ifndef MOVEMENTACTION_H
#define MOVEMENTACTION_H

#include <Action.h>


class MovementAction : public Action
{
    public:
        MovementAction();
        virtual ~MovementAction();
        virtual void execute(ActorEntity* a)=0;
        virtual void update(ActorEntity* a);

    protected:
    private:

};

#endif // MOVEMENTACTION_H
