#ifndef UNMOVEABLEBODY_H
#define UNMOVEABLEBODY_H


#include "PhysicsBody.h"
#include "GameObject.h"
#include "includes.h"


class unMoveableBody : public PhysicsBody
{
    public:
        unMoveableBody();
        virtual ~unMoveableBody();
        void update(GameObject* gObj);


    protected:
    private:
};

#endif // UNMOVEABLEBODY_H
