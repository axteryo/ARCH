#ifndef GRAPHICSBODY_H
#define GRAPHICSBODY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include "GameObject.h"


class GraphicsBody
{
    public:
        GraphicsBody(sf::Texture t);
        virtual ~GraphicsBody();
        virtual void update(GameObject& gObj) = 0;
        virtual sf::Sprite getSprite() = 0;


    protected:
    private:

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // GRAPHICSBODY_H
