#ifndef UNMOVEABLEBODY_H
#define UNMOVEABLEBODY_H


#include "PhysicsBody.h"

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
