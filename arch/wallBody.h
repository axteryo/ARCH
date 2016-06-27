#ifndef WALLBODY_H
#define WALLBODY_H

#include "PhysicsBody.h"


class wallBody : public PhysicsBody
{
    public:

        wallBody();

        virtual ~wallBody();
        virtual void update(GameObject& gObj) = 0;
        virtual void create(sf::Sprite sprite) = 0;

    protected:
    private:
};

#endif // WALLBODY_H
