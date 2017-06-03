#ifndef ACTION_H
#define ACTION_H


#include <string>
#include <vector>
#include <Box2D/Box2D.h>

class ActorEntity;

class Action
{
    public:
        Action();
        virtual ~Action();
        virtual void execute(ActorEntity* a)=0;
        virtual void cancel();
        virtual void update(ActorEntity* a)=0;
        //virtual std::string getName()= 0;
        bool getActive();
        std::string getType();
    protected:
        std::string actionType;
        bool isActive;
        int elapsed;
    private:

};

#endif // ACTION_H
