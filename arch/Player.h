#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "AnimatableGraphic.h"
#include "MoveableBody.h"


class Player : public GameObject
{
    public:
        Player(MoveableBody* p, AnimatableGraphic* g);
        virtual ~Player();
        void update();
        void setPosition(float x, float y);
        void thrust();
        void turnRight();
        void turnLeft();
        //void handleInput(sf::Keyboard k);
        sf::Sprite getSprite();

        MoveableBody* _physicsBody;
        AnimatableGraphic* _graphicsBody;
    protected:
    private:
};

#endif // PLAYER_H
