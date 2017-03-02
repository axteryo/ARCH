#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity.h"
#include "PhysicsComponent.h"



class GraphicsComponent
{
    public:
        GraphicsComponent();
        virtual ~GraphicsComponent();

        void update(entity* e);
        //sf::Vector2f getPosition();
        States::positionState getCurrentState();
        States::positionState getPreviousState();

    protected:
        sf::IntRect textureCoord;

        States::positionState currentRenderState;
        States::positionState previousRenderState;

        /**Render Notes
            Sprite Batch:Place all character textures on one image.
            Possibly make GraphicsComponent Drawable
            Look into TexturePacker shoebox**/

        //sf::Texture texture;

    private:
};

#endif // GRAPHICSCOMPONENT_H
