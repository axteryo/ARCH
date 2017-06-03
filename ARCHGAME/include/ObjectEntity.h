#ifndef OBJECTENTITY_H
#define OBJECTENTITY_H

#include <entity.h>
#include "PhysicsComponent.h"


class ObjectEntity : public entity
{
    public:
        ObjectEntity(std::string e_ID, PhysicsComponent* p);
        virtual ~ObjectEntity();
        void update();

        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);


    protected:
    private:

};

#endif // OBJECTENTITY_H
