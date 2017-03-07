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
        States::renderState getCurrentState();
        States::renderState getPreviousState();


        sf::IntRect getTextureCoord();
        void setFrame(sf::IntRect c);
    protected:




        /**Render Notes
            Sprite Batch:Place all character textures on one image.
            Possibly make GraphicsComponent Drawable
            Look into TexturePacker shoebox**/

        //sf::Texture texture;

    private:
        sf::IntRect textureCoord;
        States::renderState currentRenderState;
        States::renderState previousRenderState;
};

#endif // GRAPHICSCOMPONENT_H
