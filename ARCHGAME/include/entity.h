#ifndef ENTITY_H
#define ENTITY_H


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>




namespace States
{
   struct positionState
   {
       b2Vec2 position;
       b2Vec2 velocity;
       b2Vec2 acceleration;
       float rotation;
   };
   struct renderState
   {
       sf::Vector2f position;
       float rotation;
   };
   struct attributeState
   {
        float accel;
        float accelRate;
        float accelRateLimit;
        float velLimit;
        float brakeLimit;
        float rotationRate;
        float accel_rotationRate;
   };
   void v2f_normalize(sf::Vector2f &source);
   float to_degrees(float f);
   float to_radians(float f);
   b2Vec2 to_b2v(sf::Vector2f v);
   sf::Vector2f to_v2f(b2Vec2 b);
   sf::Vector2i to_v2i(b2Vec2 b);
   renderState to_renderState(positionState p);
   positionState to_positionState(renderState r);
   renderState lerpRenderState(renderState pre,renderState cur,double val);
   positionState lerpPositionState(positionState pre, positionState cur, float val);

}

/**Entity interface class. Foundation for building entity objects with underlying functionality**/
///NOTE to self Create a base class for other entity types to inherit from entity
///Like A base Enemy class that uses data to drive it instead of creating a different class for each enemy
///Same goes for GameObjects so to speak(interactable objects)
class entity
{
    public:
        entity();
        virtual ~entity()=0;
        virtual void setPosition(b2Vec2 p)=0;
        virtual void setRotation(float a)=0;
        virtual b2Vec2 getPosition()=0;
        virtual float getRotation()=0;

        virtual void update() = 0;
        virtual std::string getID() = 0;
        virtual std::string getType()=0;

        virtual States::positionState getCurrentState()= 0;
        virtual States::positionState getPreviousState()= 0;
        /**
        virtual void initiateCollision() = 0;
        virtual void resolveCollision() = 0;
        **/
    protected:
        std::string entity_ID;
        std::string entityType;
    private:

};

#endif // ENTITY_H
