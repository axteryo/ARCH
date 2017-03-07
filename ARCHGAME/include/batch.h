#ifndef BATCH_H
#define BATCH_H

#include "GraphicsComponent.h"


class batch : public sf::Drawable, public sf::Transformable
{
    public:
        batch();
        sf::Texture t;
        sf::VertexArray v;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual ~batch();
    protected:
    private:
};

#endif // BATCH_H
