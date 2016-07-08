#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "includes.h"

//#include "GraphicsBody.h"
//#include "PhysicsBody.h"

class GraphicsBody;
class PhysicsBody;







class GameObject
{
    public:
        GameObject(PhysicsBody& p);//,GraphicsBody()       g);
        virtual ~GameObject();
        virtual void update() = 0;
        virtual void setPosition() = 0;

        b2Vec2 b2V_position;
        b2Vec2 b2V_velocity;
        b2Vec2 b2V_rotation;

        std::string obJectId;
        int layerDepth;

        //GraphicsBody _graphicsBody;
        PhysicsBody *_physicsBody;


    protected:
    private:



};

#endif  //GAMEOBJECT_H
