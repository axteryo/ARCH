#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent()
{
    textureCoord = sf::IntRect(0,0,0,0);
    currentRenderState.position = sf::Vector2f(0,0);
    currentRenderState.rotation = 0;
    previousRenderState = currentRenderState;

}

States::renderState GraphicsComponent::getCurrentState()
{
    return currentRenderState;
}
States::renderState GraphicsComponent::getPreviousState()
{
    return previousRenderState;
}

sf::IntRect GraphicsComponent::getTextureCoord()
{
    return textureCoord;
}
void GraphicsComponent::setFrame(sf::IntRect c)
{
    textureCoord = c;
}

void GraphicsComponent::update(entity* e)
{
    previousRenderState = States::to_renderState(e->getPreviousState());
    currentRenderState = States::to_renderState(e->getCurrentState());
}



GraphicsComponent::~GraphicsComponent()
{
    //dtor
}
