#ifndef RADIUSBODY_H
#define RADIUSBODY_H
#include "PhysicsBody.h"
#include <Box2D/Box2D.h>
#include "includes.h"


class RadiusBody
{
    public:
        RadiusBody(int radius);
        virtual ~RadiusBody();

        b2CircleShape radiusShape;
        b2FixtureDef radiusFixtureDef;
        fixtureUserData* fixtureData;
        void create(PhysicsBody* p,std::string f_data);

    protected:
    private:
};

#endif // RADIUSBODY_H
