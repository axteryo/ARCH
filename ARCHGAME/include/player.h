#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"

class player : public entity
{
    public:
        player(GraphicsComponent* g,PhysicsComponent* p);
        virtual ~player();
        void setPosition(b2Vec2 p);
        void setRotation(float a);
        b2Vec2 getPosition();
        float getRotation();

        void update(float dt);

        GraphicsComponent* getGraphic();
        PhysicsComponent* getPhysics();
        /**
        virtual void initiateCollision() = 0;
        virtual void resolveCollision() = 0;
        **/
        std::string getID();


    protected:
    private:
        GraphicsComponent* gComponent;
        PhysicsComponent* pComponent;
};

#endif // PLAYER_H
