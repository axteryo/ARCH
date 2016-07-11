#ifndef STATICGRAPHIC_H
#define STATICGRAPHIC_H

#include "GraphicsBody.h"

class StaticGraphic: public GraphicsBody
{
    public:
        StaticGraphic(sf::Texture t);
        virtual ~StaticGraphic();
        void update(GameObject* gObj);
        sf::Sprite getSprite();
    protected:
    private:
};

#endif // STATICGRAPHIC_H
