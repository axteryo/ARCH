#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "GameObject.h"

#include "unMoveableBody.h"
#include "StaticGraphic.h"



class wallObject : public GameObject
{
    public:
        wallObject(unMoveableBody* p, StaticGraphic* g);
        virtual ~wallObject();
        void update();
        void setPosition(float x, float y);
        unMoveableBody* _physicsBody;
        StaticGraphic* _graphicsBody;

    protected:
    private:
};

#endif // WALLOBJECT_H
