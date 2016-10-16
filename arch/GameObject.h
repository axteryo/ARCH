#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "includes.h"

#include "GraphicsBody.h"
#include "PhysicsBody.h"

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        virtual void update() = 0;
        virtual void setPosition(float x, float y) = 0;
        virtual sf::Sprite getSprite();

        b2Vec2 b2V_position;
        b2Vec2 b2V_velocity;
        double fl_rotation;

        std::string objectId;
        int layerDepth;

    protected:
    private:



};

#endif  //GAMEOBJECT_H
