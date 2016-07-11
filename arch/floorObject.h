#ifndef FLOOROBJECT_H
#define FLOOROBJECT_H

#include "GameObject.h"
#include "StaticGraphic.h"



class floorObject : public GameObject
{
    public:
        floorObject(StaticGraphic* g);
        virtual ~floorObject();
        void update();
        void setPosition(float x, float y);

        StaticGraphic* _graphicsBody;
    protected:
    private:
};

#endif // FLOOROBJECT_H
