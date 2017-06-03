#ifndef PROJECTILEENTITY_H
#define PROJECTILEENTITY_H

#include <entity.h>


class ProjectileEntity : public entity
{
    public:
        ProjectileEntity(std::string e_ID, PhysicsComponent* p);
        virtual ~ProjectileEntity();
        void update();
        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);


    protected:
    private:

};

#endif // PROJECTILEENTITY_H
