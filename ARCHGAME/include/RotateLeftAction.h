#ifndef ROTATELEFTACTION_H
#define ROTATELEFTACTION_H

#include <Action.h>


class RotateLeftAction : public Action
{
    public:
        RotateLeftAction();
        virtual ~RotateLeftAction();
        void execute(ActorEntity* a);
    protected:
    private:
};

#endif // ROTATELEFTACTION_H
