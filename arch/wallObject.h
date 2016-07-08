#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "GameObject.h"


class wallObject : GameObject
{
    public:
        wallObject();
        virtual ~wallObject();
        virtual void update() = 0;
        virtual void setPosition() = 0;
    protected:
    private:
};

#endif // WALLOBJECT_H
