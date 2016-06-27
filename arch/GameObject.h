#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>

class PhysicsBody;
class GraphicsBody;





class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        virtual void update() = 0;
        virtual void setPosition() = 0;

        b2Vec2 position;
        b2Vec2 velocity;
        b2Vec2 rotation;

        int layerDepth;


    protected:
    private:

        GraphicsBody* _graphicsBody;
        PhysicsBody* _physicsBody;

};

#endif // GAMEOBJECT_H
