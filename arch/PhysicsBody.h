#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <string>
#include <math.h>
#include "GameObject.h"


class PhysicsBody
{
    public:
        PhysicsBody();
        virtual ~PhysicsBody();
        virtual void update(GameObject& gObj) = 0;
        virtual void create(sf::Sprite sprite) = 0;


        /**Physics properties**/
        b2Vec2 b2V2f_position;
        b2Vec2 b2V2f_velocity;
        float  fl_rotation;

          /**Physics Body definitions**/
        b2BodyDef bodyDef;
        b2Body* body;
        b2PolygonShape polygonShape;
        b2FixtureDef fixtureDef;

    protected:
    private:





};

#endif // PHYSICSBODY_H
