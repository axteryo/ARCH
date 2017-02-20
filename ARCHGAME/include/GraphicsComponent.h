#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class GraphicsComponent
{
    public:
        GraphicsComponent();
        virtual ~GraphicsComponent();
    protected:
        sf::Sprite sprite;
        sf::Texture texture;

    private:
};

#endif // GRAPHICSCOMPONENT_H
