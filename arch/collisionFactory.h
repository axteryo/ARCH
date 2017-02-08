#ifndef COLLISIONFACTORY_H
#define COLLISIONFACTORY_H

#include <Box2D/Box2D.h>
#include "GameObject.h"
#include "Actor.h"
#include "Enemy.h"
#include "includes.h"


class collisionFactory : public b2ContactListener
{
    public:
        collisionFactory();
        virtual ~collisionFactory();
        void BeginContact(b2Contact* contact);
        void Contact(b2Contact* contact);
        void checkObstaclesBetween(GameObject* A, GameObject* B);
    protected:
    private:
};

#endif // COLLISIONFACTORY_H
