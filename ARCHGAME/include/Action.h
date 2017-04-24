#ifndef ACTION_H
#define ACTION_H
//#include "ActorEntity.h"
class ActorEntity;

class Action
{
    public:
        Action();
        virtual ~Action();
        virtual void execute(ActorEntity* a)=0;
    protected:
    private:
};

#endif // ACTION_H
