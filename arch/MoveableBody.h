#ifndef MOVEABLEBODY_H
#define MOVEABLEBODY_H

#include "PhysicsBody.h"


class MoveableBody : public PhysicsBody
{
    public:
        MoveableBody();
        virtual ~MoveableBody();
        void update(GameObject& gObj);
    protected:
    private:
};

#endif //MOVEABLEBODY_H
