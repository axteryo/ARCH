#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>


class GameObj
{
    public:
        GameObj();

        void update();

        void setLocation(float lX,float lY);

        sf::Sprite getSprite();

    protected:

    private:
     /** sprite properties**/
        sf::Texture texture;
        sf::Sprite sprite;

    /** Physics properties**/
    //body definition
        b2BodyDef goBodyDef;

        //shape definition
        b2EdgeShape goPolyShape;

        //Dynamic body
        b2Body* goBody;

        //Fixture
        b2FixtureDef goFixtureDef;

        int objId;
};

#endif // GAMEOBJ_H
