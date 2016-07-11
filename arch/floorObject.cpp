#include "floorObject.h"

floorObject::floorObject(StaticGraphic* g)
{
    //ctor
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    fl_rotation = 0;

    objectId = "Object_floor";
    layerDepth = 10;

    _graphicsBody = g;

}
void floorObject::update()
{
    ///
    _graphicsBody->update(this);

}
void floorObject::setPosition(float x, float y)
{
    b2V_position = b2Vec2(x/30,y/30);
    ////

}

floorObject::~floorObject()
{
    //dtor
}
