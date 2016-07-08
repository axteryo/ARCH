#ifndef MOVEABLEBODY_H
#define MOVEABLEBODY_H

#include "PhysicsBody.h"


class MoveableBody : public PhysicsBody
{
    public:
        MoveableBody();
        virtual ~MoveableBody();
        virtual void update(GameObject& gObj) = 0;
    protected:
    private:
};

#endif //MOVEABLEBODY_H
