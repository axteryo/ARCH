#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "GameObject.h"

#include "unMoveableBody.h"



class wallObject : public GameObject
{
    public:
        wallObject();
        virtual ~wallObject();
        void update();
        void setPosition();
        unMoveableBody* _physicsBody;
    protected:
    private:
};

#endif // WALLOBJECT_H
