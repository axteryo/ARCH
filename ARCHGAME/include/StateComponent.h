#ifndef STATECOMPONENT_H
#define STATECOMPONENT_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
   struct movementAttributeState
   {
        float accel;
        float accelRate;
        float accelRateLimit;
        float velLimit;
        float brakeLimit;
        float rotationRate;
        float accel_rotationRate;
   };
   struct statusAttributeState
   {
       float maxHealth;
       float minHealth;
       float curHealth;
   };
   struct attackAttributeState
   {
       bool isAttacking;
       b2Vec2 direction;
       std::string attack;
       std::string impactType;
       float force;
       int damage;
   };

namespace State
{
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

class StateComponent
{
    public:
        StateComponent();
        virtual ~StateComponent();
        void setPositionState(positionState p);
        void setRenderState(renderState r);
        void setMovementAttributeState(movementAttributeState m);
        void setStatusAttributeState(statusAttributeState s);
        void setAttackAttributeState(attackAttributeState a);

        positionState getPositionState();
        renderState getRenderState();
        movementAttributeState getMovementAttributeState();
        statusAttributeState getStatusAttributeState();
        attackAttributeState getAttackAttributeState();

        bool isAttacking();
        bool isRotating();
        bool isAlive();
        bool isAccelerating();

        void update();
    protected:
    private:
        positionState position_state;
        renderState render_state;
        movementAttributeState movement_attributeState;
        statusAttributeState status_attributeState;
        attackAttributeState attack_attributeState;
};

#endif // STATECOMPONENT_H
