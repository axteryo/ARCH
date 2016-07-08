#ifndef UNMOVEABLEBODY_H
#define UNMOVEABLEBODY_H


#include "PhysicsBody.h"

class unMoveableBody : public PhysicsBody
{
    public:
        unMoveableBody();
        virtual ~unMoveableBody();
        virtual void update(GameObject& gObj) = 0;


    protected:
    private:
};

#endif // UNMOVEABLEBODY_H
