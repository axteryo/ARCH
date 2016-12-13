#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <Box2D/Box2D.h>
#include "includes.h"



class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        virtual void update() = 0;
        virtual void setPosition(float x, float y) = 0;
        //virtual sf::Sprite getSprite();

        b2Vec2 b2V_position;
        /**NOTE TO SELF
        Derive an ACTOR CLASS FROM GAMEOBJECT IN FUTURE
        A wall does not need a topSpeed or velocity**/
        double fl_rotation;

        std::string objectId;
        int layerDepth;

    protected:
    private:



};

#endif  //GAMEOBJECT_H
