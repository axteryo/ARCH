#ifndef SPRITEBATCHER_H
#define SPRITEBATCHER_H

#include "GraphicsComponent.h"
#include <SFML/Graphics.hpp>


class SpriteBatcher// : public sf::Drawable, public sf::Transformable
{
    public:
        SpriteBatcher();
        virtual ~SpriteBatcher();
        void addToBatch(GraphicsComponent* gComponent);
        void batch();
    protected:


    private:
        sf::VertexArray batch_vertArray;
        sf::Texture  batch_texture;
        //void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // SPRITEBATCHER_H
