#ifndef SPRITEBATCHER_H
#define SPRITEBATCHER_H

#include "GraphicsComponent.h"
#include "entity.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>


class SpriteBatcher// : public sf::Drawable, public sf::Transformable
{
    public:
        SpriteBatcher();
        virtual ~SpriteBatcher();
        void setBatchTexture(sf::Image i);
        void addToBatch(entity* e);
        void batch();
    protected:


    private:
        sf::VertexArray batch_vertArray;
        sf::Texture  batch_texture;
        //void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // SPRITEBATCHER_H
