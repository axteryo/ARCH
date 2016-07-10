#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "includes.h"

//#include "GraphicsBody.h"
#include "PhysicsBody.h"

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        virtual void update() = 0;
        virtual void setPosition() = 0;

        b2Vec2 b2V_position;
        b2Vec2 b2V_velocity;
        b2Vec2 b2V_rotation;

        std::string objectId;
        int layerDepth;

    protected:
    private:



};

#endif  GAMEOBJECT_H
